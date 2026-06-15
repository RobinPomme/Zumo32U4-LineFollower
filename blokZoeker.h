#ifndef BLOKZOEKER_H
#define BLOKZOEKER_H

#include <Wire.h>
#include <Zumo32U4.h>
#include "proximity.h"
#include "rijden.h"
#include "lijn.h"
#include "encoder.h"

class BlokZoeker {
public:
    BlokZoeker(ProximitySensor*, Rijden*, LijnSensor*, Encoder*);
    bool zoekBlok();
    void rijNaarMidden();
    void duwBlok();
    void setBlokGevonden(bool);
private:
    ProximitySensor* proxSensors;
    Rijden* motors;
    LijnSensor* lineSensors;
    Encoder* encoder;
    bool blokGevonden;
};

#endif // BLOKZOEKER_H
