#include "rijden.h"
#include "xbee.h"

Xbee xbee;  //maak een nieuw object xbee van klasse Xbee
Zumo32U4ButtonB knopB;
Zumo32U4ButtonA knopA;
Zumo32U4ButtonC knopC;
Rijden Motors(&xbee);
bool pauzeTijd;
bool blokjesTijd;


void setup() {
  Serial.begin(9600);  //start serial output via de kabel (deze wordt afgebroken zodra de kabel is losgekoppend (daar is de xbee voor))
  delay(1000);
  Serial.println("De kabel kan er nu uit getrokken worden.");
  pauzeTijd = true;
  blokjesTijd = false;
}

void loop() {
  delay(100);
  switch (xbee.leesXbee()) { //leest de xbee uit voor het volgende commando
    case 'w':
      Motors.setSnelheid(CRUISE_SPEED);
      break; //naar voren gaan
    case 's':
      Motors.setSnelheid(CRUISE_SPEED);
      Motors.Achteruit();
      break; //achteruit gaan
    case ' ':
      Motors.Stop();
      break; //stoppen (met spatiebalk)
    case 'a':
      Motors.setSnelheid(CRUISE_SPEED / 2);
      Motors.naarLinks();
      break; //naar links gaan
    case 'd':
      Motors.setSnelheid(CRUISE_SPEED / 2);
      Motors.naarRechts();
      break; //naar rechts gaan
  }
}