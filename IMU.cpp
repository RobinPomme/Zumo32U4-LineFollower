#include "IMU.h"
#include <Wire.h>  ///< Wire is nodig voor I2C communicatie met de IMU hardware

/**
 * @brief Constructor: maakt het IMU object aan, sensoren worden via begin() opgestart
 */
IMU::IMU() {}

/**
 * @brief begin() initialiseert de IMU hardware via de I2C bus.
 *
 * Wire.begin() start de I2C verbinding op.
 * imu.init() controleert of de sensor gevonden wordt op de bus.
 * imu.enableDefault() zet de standaard meetbereiken aan voor gyro, accel en mag.
 *
 * @return true als alles gelukt is, anders false.
 */
bool IMU::begin()
{
    Wire.begin();
    if (!imu.init())
    {
        return false;
    }
    imu.enableDefault();
    return true;
}

/**
 * @brief update() leest de nieuwste ruwe sensorwaarden uit van alle drie de sensoren
 * en slaat ze op in accel, gyro en mag via hun set() functies.
 *
 * Wordt elke loop-cyclus aangeroepen vanuit updateAngleEstimate() in blinkdemo.ino.
 */
void IMU::update()
{
    imu.readAcc();   ///< Leest de nieuwste accelerometerwaarden in (imu.a.x/y/z)
    imu.readGyro();  ///< Leest de nieuwste gyroscoopwaarden in (imu.g.x/y/z)
    imu.readMag();   ///< Leest de nieuwste magnetometerwaarden in (imu.m.x/y/z)

    accel.set(imu.a.x, imu.a.y, imu.a.z);  ///< Accelerometer: x, y, z versnelling
    gyro.set(imu.g.x, imu.g.y, imu.g.z);   ///< Gyroscoop: x, y, z rotatiesnelheid
    mag.set(imu.m.x, imu.m.y, imu.m.z);    ///< Magnetometer: x, y, z magneetveld
}
