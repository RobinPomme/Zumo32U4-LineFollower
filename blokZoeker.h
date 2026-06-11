#ifndef BLOKZOEKER_H
#define BLOKZOEKER_H

#include <Wire.h>
#include <Zumo32U4.h>
#include "proximity.h"
#include "rijden.h"
#include "lijn.h"

class BlokZoeker {
public:
    BlokZoeker(ProximitySensor*, Rijden*, LijnSensor*);
    bool zoekBlok();
    void rijNaarMidden();
    void duwBlok();
    void setBlokGevonden(bool);
private:
    ProximitySensor* proxSensors;
    Rijden* motors;
    LijnSensor* lineSensors;
    bool blokGevonden;
};

#endif // BLOKZOEKER_H
