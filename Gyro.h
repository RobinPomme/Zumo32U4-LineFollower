#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>

class Gyro
{
public:
    int16_t x;
    int16_t y;
    int16_t z;

    Gyro() : x(0), y(0), z(0) {}

    void set(int16_t gx, int16_t gy, int16_t gz)
    {
        x = gx;
        y = gy;
        z = gz;
    }
};

#endif