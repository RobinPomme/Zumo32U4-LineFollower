#include "rijden.h"
#include "xbee.h"
#include "lijn.h"
#include "proximity.h"
#include "encoder.h"
#include "blokZoeker.h"

// Maak een object aan voor alle drie de knoppen op de Zumo
Zumo32U4ButtonA knopA;
Zumo32U4ButtonB knopB;
Zumo32U4ButtonC knopC;

// 
Xbee xbee;
// 
LijnSensor lijnSensor(&xbee);
Rijden Motors(&xbee, &lijnSensor);
ProximitySensor proximitySensor(&xbee);
Encoder encoder;
BlokZoeker blokZoeker(&proximitySensor, &Motors, &lijnSensor, &encoder);

bool pauzeTijd;
bool blokjesTijd;

void setup() {
  Serial.begin(9600);  //start serial output via de kabel (deze wordt afgebroken zodra de kabel is losgekoppend (daar is de xbee voor))
  delay(1000);
  Serial.println("De kabel kan er nu uit getrokken worden.");
  xbee.printLineBreak();
  xbee.printXbee("Om te beginnen, druk op knop b");
  xbee.printLineBreak();
  knopB.waitForButton();
  Motors.initialiseer();  //initialiseert de motoren en begint daarna met het kalibreren van de lijnsensors
  pauzeTijd = true;
  blokjesTijd = false;
}

void loop() {
  if (knopA.isPressed()) {
    pauzeTijd = true;
  }

  if (knopC.isPressed()) {
    pauzeTijd = false;
  }

  if (!pauzeTijd) {
    int lijnPositie = lijnSensor.leesPositie();

    if(blokjesTijd) {
      xbee.printXbee("Blokjestijd True");
      blokZoeker.rijNaarMidden();
      xbee.printXbee("Midden reached");
      blokZoeker.zoekBlok();
      xbee.printXbee("We gaan duwe :)");
      blokZoeker.duwBlok(&xbee);
      pauzeTijd = true;
    } else {
      Motors.pidController(lijnPositie);
    }
  } else {
    Motors.Stop();
  }
}
