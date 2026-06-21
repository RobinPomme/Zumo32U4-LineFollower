#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <Zumo32U4IMU.h>
#include "gyro.h"
#include "accelerometer.h"
#include "magnetometer.h"

/**
 * @brief De IMU klasse is de hoofdklasse voor alle sensordata.
 *
 * Hij beheert de accelerometer, gyroscoop en magnetometer.
 * Via begin() wordt de hardware opgestart en via update() worden
 * de nieuwste sensorwaarden uitgelezen en opgeslagen.
 */
class IMU
{
private:
    Zumo32U4IMU imu;  ///< De interne Pololu hardware driver die de fysieke sensor aanstuurt

public:
    /**
     * @brief Constructor: maakt het IMU object aan
     */
    IMU();

    /**
     * @brief begin() initialiseert de IMU hardware via I2C.
     * @return true als de sensor gevonden en opgestart is, anders false.
     */
    bool begin();

    /**
     * @brief update() leest de nieuwste waarden uit van alle drie de sensoren
     * en slaat ze op in accel, gyro en mag via hun set() functies.
     */
    void update();

    Gyro gyro;           ///< Gyroscoop: meet rotatieSnelheid in graden per seconde
    Accelerometer accel; ///< Accelerometer: meet zwaartekracht, gebruikt voor hoekberekening
    Magnetometer mag;    ///< Magnetometer: meet het magnetisch veld voor richting
};

#endif
