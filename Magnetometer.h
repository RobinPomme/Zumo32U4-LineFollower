#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H

#include <Arduino.h>

class Magnetometer
{
public:
    int16_t x;
    int16_t y;
    int16_t z;

    Magnetometer() : x(0), y(0), z(0) {}

    void set(int16_t mx, int16_t my, int16_t mz)
    {
        x = mx;
        y = my;
        z = mz;
    }
};

#endif