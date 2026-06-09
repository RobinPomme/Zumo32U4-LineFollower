#ifndef BLOKZOEKER_H
#define BLOKZOEKER_H

#include <Wire.h>
#include <Zumo32U4.h>
#include "proximity.h"
#include "rijden.h"

class BlokZoeker {
public:
    BlokZoeker(ProximitySensor*, Rijden*);
    void zoekBlok();
    void rijNaarMidden();
    void zoekBlok();
    void duwBlok();
private:
    ProximitySensor* proxSensors;
    Rijden* motors;
    bool blokGevonden;
};

#endif // BLOKZOEKER_H
