#include "proximity.h"

ProximitySensor::ProximitySensor(Xbee* x):xbee(x) {
    zumoProxSensors.initThreeSensors();
    objectDrempelwaarde = defaultObjectDrempelwaarde;
}

bool ProximitySensor::objectZichtbaar() {
    zumoProxSensors.read();
    return (zumoProxSensors.countsFrontWithLeftLeds() >= objectDrempelwaarde) || (zumoProxSensors.countsFrontWithRightLeds() >= objectDrempelwaarde);
}

/*  -1 = Beide 0
    0 = Beide L & R gelijke waarde
    1 = Links
    2 = Rechts
    Default 0 */
int ProximitySensor::objectRichting() {
    int direction = 0;
    zumoProxSensors.read();

    if (this->objectZichtbaar()) {
        int ledWaardeLinks = zumoProxSensors.countsFrontWithLeftLeds();
        int ledWaardeRechts = zumoProxSensors.countsFrontWithRightLeds();

        if (ledWaardeLinks == ledWaardeRechts){
            return 0;
        } else if (ledWaardeLinks > ledWaardeRechts) {
            return 1;
        } else if (ledWaardeRechts > ledWaardeLinks) {
            return 2;
        }
    } else {
        return -1;
    }
}

void ProximitySensor::printAlles() const{
    zumoProxSensors.read();

    xbee->printLineBreak();

    xbee->print("\nReading: ");
    xbee->print("\nLeft: " + String(zumoProxSensors.countsFrontWithLeftLeds()));
    xbee->print("\nRight: " + String(zumoProxSensors.countsFrontWithRightLeds()));

    xbee->print("\nobjectZichtbaar: ");
    xbee->print(objectZichtbaar() ? "True" : "False");

    xbee->printLineBreak();
}

/** \brief Geeft de huidige drempelwaarde objectafstandmeting. */
void ProximitySensor::setObjectDrempelwaarde(int threshold) {
    this->objectDrempelwaarde = threshold;
}
