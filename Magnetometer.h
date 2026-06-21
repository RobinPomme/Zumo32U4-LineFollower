#ifndef MAGNETOMETER_H
#define MAGNETOMETER_H

#include <Arduino.h>

// De Magnetometer klasse slaat de ruwe sensorwaarden op van de magnetometer.
// De magnetometer meet het magnetisch veld op drie assen.
// De waarden kunnen gebruikt worden om de rijrichting van de robot te bepalen.
class Magnetometer
{
public:
    int16_t x;  // Magnetisch veld op de X-as (links/rechts)
    int16_t y;  // Magnetisch veld op de Y-as (omhoog/omlaag)
    int16_t z;  // Magnetisch veld op de Z-as (voor/achter)

    // Constructor: zet alle waarden standaard op 0 bij het aanmaken van het object
    Magnetometer() : x(0), y(0), z(0) {}

    // set() wordt aangeroepen vanuit IMU::update() om de nieuwste sensorwaarden op te slaan.
    // mx, my, mz zijn de ruwe waarden die direct uit de Zumo32U4IMU hardware komen.
    void set(int16_t mx, int16_t my, int16_t mz)
    {
        x = mx;
        y = my;
        z = mz;
    }
};

#endif
