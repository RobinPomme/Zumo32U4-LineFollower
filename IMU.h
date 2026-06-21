#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <Zumo32U4IMU.h>
#include "gyro.h"
#include "accelerometer.h"
#include "magnetometer.h"

class IMU
{
private:
    Zumo32U4IMU imu;

public:
    IMU();
    bool begin();
    void update();

    Gyro gyro;
    Accelerometer accel;
    Magnetometer mag;
};

#endif