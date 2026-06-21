#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>

// De Gyro klasse slaat de ruwe sensorwaarden op van de gyroscoop.
// De gyroscoop meet de rotatieSnelheid van de robot in graden per seconde.
// Specifiek wordt de y-as gebruikt in de formule: imu.gyro.y * 0.07f om de rotatieSnelheid te berekenen.
class Gyro
{
public:
    int16_t x;  // RotatieSnelheid om de X-as (kantelen voor/achter)
    int16_t y;  // RotatieSnelheid om de Y-as (kantelen links/rechts) → wordt gebruikt voor balanceren
    int16_t z;  // RotatieSnelheid om de Z-as (draaien op de plek)

    // Constructor: zet alle waarden standaard op 0 bij het aanmaken van het object
    Gyro() : x(0), y(0), z(0) {}

    // set() wordt aangeroepen vanuit IMU::update() om de nieuwste sensorwaarden op te slaan.
    // gx, gy, gz zijn de ruwe waarden die direct uit de Zumo32U4IMU hardware komen.
    void set(int16_t gx, int16_t gy, int16_t gz)
    {
        x = gx;
        y = gy;
        z = gz;
    }
};

#endif
