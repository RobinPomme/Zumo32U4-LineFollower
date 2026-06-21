#ifndef RIJDEN_H
#define RIJDEN_H

#include <Zumo32U4.h>
#include "xbee.h"

#define MAX_SPEED 400
#define CRUISE_SPEED 300
#define CALIBRATE_SPEED 200

#define CONSTANT_P 0.75
#define CONSTANT_I 0.05
#define CONSTANT_D 1.55 //dit zijn nu mooie waarden (Kp = 0.75, Ki = 0.05, Kd = 1.55 met snelheid = 300 en max in pid = max_speed)

#define BUFFER_COUNT 5

class Rijden {
  private:
    bool resetBuffer[BUFFER_COUNT];
    int snelheid[2]; //een variabele om de snelheid bij te houden
    int error;
    int afgeleide;
    long integraal;
    Zumo32U4Motors motorenVanZumo; //maakt een nieuw object voor de motoren van de zumo
    Xbee* xbeePointer;
  public:
    Rijden(Xbee*);
    int getSnelheid() const;
    void setSnelheid(int snelheid);
    void setSnelheid(int snelheidL, int snelheidR);
    void initialiseer();
    void naarLinks();
    void naarRechts();
    void Achteruit();
    void Stop(); //functie definities
};

#endif