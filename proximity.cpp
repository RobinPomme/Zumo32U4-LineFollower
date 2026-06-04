#include "proximity.h"

ProximitySensor::ProximitySensor(Xbee* x):xbee(x) {
    zumoProxSensors.initThreeSensors();
    objectThreshold = defaultObjectThreshold;
}

bool ProximitySensor::objectVisible() {
    // zumoProxSensors.read();
    return (zumoProxSensors.countsFrontWithLeftLeds() >= objectThreshold) || (zumoProxSensors.countsFrontWithRightLeds() >= objectThreshold);
}

void ProximitySensor::printReadings() const{
    zumoProxSensors.read();

    xbee->printLineBreak();

    xbee->print("\nReading: ");
    xbee->print("\nLeft: " + String(zumoProxSensors.countsFrontWithLeftLeds()));
    xbee->print("\nRight: " + String(zumoProxSensors.countsFrontWithRightLeds()));

    xbee->print("\nobjectVisible: ");
    xbee->print(objectVisible() ? "True" : "False");

    xbee->printLineBreak();
}

/** \brief Geeft de huidige drempelwaarde objectafstandmeting. */
void ProximitySensor::setObjectThreshold(int threshold) {
    this->objectThreshold = threshold;
}
