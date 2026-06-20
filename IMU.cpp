#include "IMU.h"
#include <Wire.h>  // Fix 1: added missing Wire include

IMU::IMU() {}

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

void IMU::update()
{
    imu.readAcc();   // Fix 2: was readAccelerometer()
    imu.readGyro();
    imu.readMag();   // Fix 3: was readMagnetometer()

    accel.set(imu.a.x, imu.a.y, imu.a.z);
    gyro.set(imu.g.x, imu.g.y, imu.g.z);
    mag.set(imu.m.x, imu.m.y, imu.m.z);
}
