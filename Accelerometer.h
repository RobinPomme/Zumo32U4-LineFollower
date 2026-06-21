#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Arduino.h>

// De Accelerometer klasse slaat de ruwe sensorwaarden op van de accelerometer.
// De x, y en z waarden worden gebruikt om de kanteling van de robot te berekenen.
// Specifiek worden x en z gebruikt in de formule: atan2(ax, az) om de hoek te bepalen.
class Accelerometer
{
public:
    int16_t x;  // Versnelling op de X-as (horizontaal, links/rechts)
    int16_t y;  // Versnelling op de Y-as (omhoog/omlaag)
    int16_t z;  // Versnelling op de Z-as (voor/achter)

    // Constructor: zet alle waarden standaard op 0 bij het aanmaken van het object
    Accelerometer() : x(0), y(0), z(0) {}

    // set() wordt aangeroepen vanuit IMU::update() om de nieuwste sensorwaarden op te slaan.
    // ax, ay, az zijn de ruwe waarden die direct uit de Zumo32U4IMU hardware komen.
    void set(int16_t ax, int16_t ay, int16_t az)
    {
        x = ax;
        y = ay;
        z = az;
    }
};

#endif
