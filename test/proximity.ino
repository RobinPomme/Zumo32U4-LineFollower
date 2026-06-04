#include "proximity.h"

Xbee xbee;
ProximitySensor proxSensor(&xbee);

void setup() {
    Serial.begin(115200);
    
    delay(200);

    Serial.println("Proximity sensor init");
}

void loop() {
    proxSensor.printReadings();
    delay(1000);
}
