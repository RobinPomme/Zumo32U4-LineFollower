#include "proximity.h"

ProximitySensor::ProximitySensor(Xbee* x):xbee(x) {
    zumoProxSensors.initThreeSensors();
    objectDrempelwaarde = defaultObjectDrempelwaarde;
}

bool ProximitySensor::objectZichtbaar() {
    zumoProxSensors.read();
    return (zumoProxSensors.countsFrontWithLeftLeds() >= objectDrempelwaarde) || (zumoProxSensors.countsFrontWithRightLeds() >= objectDrempelwaarde);
}

int ProximitySensor::objectRichting() {
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

    xbee->printXbee("\nReading: ");
    xbee->printXbee("\nLeft: " + String(zumoProxSensors.countsFrontWithLeftLeds()));
    xbee->printXbee("\nRight: " + String(zumoProxSensors.countsFrontWithRightLeds()));

    xbee->printXbee("\nobjectZichtbaar: ");
    xbee->printXbee(objectZichtbaar() ? "True" : "False");

    xbee->printLineBreak();
}

void ProximitySensor::setObjectDrempelwaarde(int drempelwaarde) {
    this->objectDrempelwaarde = drempelwaarde;
}
