#ifndef RIJDEN_H
#define RIJDEN_H

#include <Zumo32U4.h>
#include "lijn.h"

#define MAX_SPEED 400
#define CRUISE_SPEED 250
#define CALIBRATE_SPEED 200
#define CONSTANT_P 0.55
#define CONSTANT_I 0
#define CONSTANT_D 0

class Rijden {
  private:
    int snelheid[2]; //een variabele om de snelheid bij te houden
    int richting; //een variabele om de richting in op te slaan
    int error;
    int afgeleide;
    long integraal;
    Zumo32U4Motors motorenVanZumo; //maakt een nieuw object voor de motoren van de zumo
    LijnSensor* lineSensors;
    Xbee* xbeePointer;
  public:
    Rijden(Xbee*, LijnSensor*);
    int getSnelheid() const;
    void setSnelheid(int snelheid);
    void setSnelheid(int snelheidL, int snelheidR);
    void initialiseer();
    void naarLinks();
    void naarRechts();
    void Achteruit();
    void stuur(int lijnPositie);
    void pidController(int lijnPositie);
    void Stop(); //functie definities
};

#endif