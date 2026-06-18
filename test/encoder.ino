// main.ino
#include "rijden.h"
#include "xbee.h"
#include "lijn.h"
#include "encoder.h"

Xbee xbee;
Zumo32U4ButtonA knopA;
Zumo32U4ButtonB knopB;
Zumo32U4ButtonC knopC;

LijnSensor lijnSensor(&xbee);
Rijden Motors(&xbee, &lijnSensor);
Encoder encoder;

bool pauzeTijd   = true;
bool blokjesTijd = false;

const unsigned long ENCODER_INTERVAL = 500;
unsigned long vorigeEncoderTijd = 0;

void stuurEncoderData() {
    int links  = encoder.getCountsLeft();
    int rechts = encoder.getCountsRight();

    xbee.printLineBreak();
    xbee.printXbee("=== Encoder waarden ===");
    xbee.printXbee("Links  (counts): " + String(links));
    xbee.printXbee("Rechts (counts): " + String(rechts));
    xbee.printXbee("Links  (cm): " + String(encoder.countsToCm(links)));
    xbee.printXbee("Rechts (cm): " + String(encoder.countsToCm(rechts)));
    xbee.printLineBreak();
}

void setup() {
    Serial.begin(9600);
    delay(1000);
    Serial.println("De kabel kan er nu uit getrokken worden.");

    xbee.printLineBreak();
    xbee.printXbee("Om te beginnen, druk op knop B");
    xbee.printLineBreak();

    knopB.waitForButton();

    Motors.initialiseer();
    lijnSensor.kalibreerAlles();
    encoder.init();

    pauzeTijd    = true;
    blokjesTijd  = false;

}



void loop() {
    // Knop A → pauzeer
    if (knopA.isPressed()) {
        pauzeTijd = true;
    }

    // Knop C → hervat
    if (knopC.isPressed()) {
        pauzeTijd = false;
    }

    unsigned long nu = millis();
    if (nu - vorigeEncoderTijd >= ENCODER_INTERVAL) {
        vorigeEncoderTijd = nu;
        stuurEncoderData();
    }

    if (!pauzeTijd) {
        int lijnPositie = lijnSensor.leesPositie();

        //if (blokjesTijd) {
            // TODO: blokjes logica hier
            // bv. Motors.rijAfstand(Encoder::getCountsLeft(), 20.0f);
        //} else {
            Motors.pidController(lijnPositie);
        //}

    } else {
        Motors.Stop();
    }
}