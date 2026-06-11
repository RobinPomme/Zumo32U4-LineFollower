#ifndef BLOKZOEKER_H
#define BLOKZOEKER_H

#include <Wire.h>
#include <Zumo32U4.h>
#include "proximity.h"
#include "rijden.h"

class BlokZoeker {
public:
    BlokZoeker(ProximitySensor*, Rijden*);
    bool zoekBlok();
    void rijNaarMidden();
    void duwBlok();
private:
    ProximitySensor* proxSensors;
    Rijden* motors;
    bool blokGevonden;
};

#endif // BLOKZOEKER_H
