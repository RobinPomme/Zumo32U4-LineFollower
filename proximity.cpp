#include "proximity.h"

ProximitySensor::ProximitySensor(Xbee* x):xbee(x) {
    zumoProxSensors.initThreeSensors();
    objectThreshold = defaultObjectThreshold;
}

bool ProximitySensor::objectVisible() {
    // zumoProxSensors.read();
    return (zumoProxSensors.countsFrontWithLeftLeds() >= objectThreshold) || (zumoProxSensors.countsFrontWithRightLeds() >= objectThreshold);
}

/*  -1 = Beide 0
    0 = Beide L & R gelijke waarde
    1 = Links
    2 = Rechts
    Default 0 */
int ProximitySensor::objectDirection() {
    int direction = 0;
    // zumoProxSensors.read();

    if (this->objectvisible()) {
        int leftLedReading = zumoProxSensors.countsFrontWithLeftLeds();
        int rightLedReading = zumoProxSensors.countsFrontWithRightLeds();

        if (leftLedReading == rightLedReading){
            return 0;
        } else if (leftLedReading > rightLedReading) {
            return 1;
        } else if (rightLedReading > leftLedReading) {
            return 2;
        }
    } else {
        return -1;
    }
}

void ProximitySensor::printFullReadings() const{
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
