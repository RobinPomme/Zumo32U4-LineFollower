#include "proximity.h"
#include "blokZoeker.h"
#include "rijden.h"
#include "lijn.h"

Xbee xbee;
ProximitySensor proxSensor(&xbee);
LijnSensor lijnsens(&xbee);
Rijden motor(&xbee, &lijnsens);
BlokZoeker blok(&proxSensor, &motor);

void setup() {
    Serial.begin(115200);
    
    delay(200);

    Serial.println("Proximity sensor init");

    motor.initialiseer();
    Serial.println("Motor init");
}

void loop() {
    // proxSensor.printAlles();

    // proxSensor.printAlles();
    blok.zoekBlok();
}
