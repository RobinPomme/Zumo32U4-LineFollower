#include <Wire.h>
#include <Zumo32U4.h>
#include <math.h>
#include "imu.h"

Zumo32U4Motors motors;
Zumo32U4ButtonB buttonB;
IMU imu;

bool started = false;
int state = 0;

unsigned long stateStartTime = 0;
unsigned long lastPrintTime  = 0;
unsigned long lastMicros     = 0;

const int approachSpeed   = 200;
const int exitSpeed       = 350;
const int maxBalanceSpeed = 80;
const int minBalanceSpeed = 55;
const int motorLimit      = 400;
const int leftTrim        = 0;

const unsigned long minApproachMs  = 1025;  // ← was 1050
const unsigned long maxApproachMs  = 3000;

const unsigned long settleTimeMs   = 800;
const unsigned long balanceTimeMs  = 3000;
const unsigned long exitTimeMs     = 2000;

const float levelAngleThreshold = 1.5f;

const float balanceKp     = 6.0f;
const float balanceKd     = 0.25f;
const float gyroWeight    = 0.985f;
const float angleDeadband = 0.7f;
const int   controlSign   = -1;

float angleDeg          = 0.0f;
float gyroRateDegPerSec = 0.0f;
float balanceTargetAngle = 0.0f;

float readAccelAngleDeg()
{
    float ax = (float)imu.accel.x;
    float az = (float)imu.accel.z;
    return atan2(ax, az) * 180.0f / PI;
}

float readGyroRateDegPerSec()
{
    return (float)imu.gyro.y * 0.07f;
}

void updateAngleEstimate()
{
    imu.update();

    unsigned long now = micros();
    float dt = (now - lastMicros) / 1000000.0f;
    lastMicros = now;

    if (dt <= 0.0f || dt > 0.05f)
        dt = 0.01f;

    float accelAngle = readAccelAngleDeg();
    gyroRateDegPerSec = readGyroRateDegPerSec();

    float predictedAngle = angleDeg + (gyroRateDegPerSec * dt);
    angleDeg = (gyroWeight * predictedAngle) + ((1.0f - gyroWeight) * accelAngle);
}

void setMatchedSpeeds(int speed)
{
    if (speed != 0 && abs(speed) < minBalanceSpeed)
        speed = (speed > 0) ? minBalanceSpeed : -minBalanceSpeed;

    speed = constrain(speed, -motorLimit, motorLimit);
    motors.setSpeeds(speed + leftTrim, speed);
}

void stopMotors()
{
    motors.setSpeeds(0, 0);
}

void balanceOnPoint()
{
    float error = angleDeg - balanceTargetAngle;

    if (fabs(error) < angleDeadband)
        error = 0.0f;

    int speed = (int)(controlSign * ((balanceKp * error) + (balanceKd * gyroRateDegPerSec)));
    speed = constrain(speed, -maxBalanceSpeed, maxBalanceSpeed);
    setMatchedSpeeds(speed);
}

void printDebug()
{
    if (millis() - lastPrintTime < 120)
        return;

    lastPrintTime = millis();

    Serial.print("State: ");      Serial.print(state);
    Serial.print(" | Angle: ");   Serial.print(angleDeg);
    Serial.print(" | Target: ");  Serial.print(balanceTargetAngle);
    Serial.print(" | Gyro: ");    Serial.print(gyroRateDegPerSec);
    Serial.print(" | AccelX: ");  Serial.print(imu.accel.x);
    Serial.print(" | AccelZ: ");  Serial.println(imu.accel.z);
}

void resetRun()
{
    started = false;
    state   = 0;
    stopMotors();
    Serial.println("Run klaar. Druk opnieuw op Button B.");
}

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    if (!imu.begin())
    {
        Serial.println("IMU niet gevonden!");
        while (1) {}
    }

    imu.update();
    angleDeg           = readAccelAngleDeg();
    balanceTargetAngle = angleDeg;
    lastMicros         = micros();
    stopMotors();

    Serial.println("Druk op Button B om een run te starten.");
}

void loop()
{
    updateAngleEstimate();
    printDebug();

    if (!started)
    {
        stopMotors();

        if (buttonB.getSingleDebouncedPress())
        {
            started        = true;
            state          = 1;
            stateStartTime = millis();
            Serial.println("Start run -> wipwap op!");
        }

        delay(2);
        return;
    }

    switch (state)
    {
    // ── State 1: Rijd omhoog tot wipwap horizontaal is (= grijze lijn) ──
    case 1:
        motors.setSpeeds(approachSpeed + leftTrim, approachSpeed);
        {
            unsigned long elapsed = millis() - stateStartTime;

            bool atPivot    = (elapsed >= minApproachMs) && (fabs(angleDeg) < levelAngleThreshold);
            bool safetyStop = (elapsed >= maxApproachMs);

            if (atPivot || safetyStop)
            {
                stopMotors();
                state          = 2;
                stateStartTime = millis();
                Serial.println(atPivot ? "Grijze lijn bereikt! -> settle" : "Safety stop -> settle");
            }
        }
        break;

    // ── State 2: Stilstaan, hoek opslaan als doelhoek ──────────────────
    case 2:
        stopMotors();

        if (millis() - stateStartTime >= settleTimeMs)
        {
            balanceTargetAngle = angleDeg;
            state              = 3;
            stateStartTime     = millis();
            Serial.println("Settle klaar -> 3 sec balanceren");
        }
        break;

    // ── State 3: 3 seconden balanceren op grijze lijn ──────────────────
    case 3:
        balanceOnPoint();

        if (millis() - stateStartTime >= balanceTimeMs)
        {
            state          = 4;
            stateStartTime = millis();
            Serial.println("3 sec voorbij -> doorrijden!");
        }
        break;

    // ── State 4: Rijd van de wipwap af ─────────────────────────────────
    case 4:
        motors.setSpeeds(exitSpeed + leftTrim, exitSpeed);

        if (millis() - stateStartTime >= exitTimeMs)
        {
            stopMotors();
            resetRun();
        }
        break;

    default:
        resetRun();
        break;
    }

    delay(2);
}
