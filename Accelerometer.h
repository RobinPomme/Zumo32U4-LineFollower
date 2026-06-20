#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Arduino.h>

class Accelerometer
{
public:
    int16_t x;
    int16_t y;
    int16_t z;

    Accelerometer() : x(0), y(0), z(0) {}

    void set(int16_t ax, int16_t ay, int16_t az)
    {
        x = ax;
        y = ay;
        z = az;
    }
};

#endif