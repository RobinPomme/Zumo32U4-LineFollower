#include "rijden.h"
#include "xbee.h"
#include "lijn.h"

Xbee xbee;  //maak een nieuw object xbee van klasse Xbee
Zumo32U4ButtonB knopB;
Zumo32U4ButtonA knopA;
Zumo32U4ButtonC knopC;
LijnSensor lijnSensor(&xbee);
Rijden Motors(&xbee, &lijnSensor);
bool pauzeTijd;


void setup() {
  Serial.begin(9600);  //start serial output via de kabel (deze wordt afgebroken zodra de kabel is losgekoppend (daar is de xbee voor))
  delay(1000);
  Serial.println("De kabel kan er nu uit getrokken worden.");
  xbee.printLineBreak();
  xbee.printXbee("Om te beginnen, druk op knop b");
  xbee.printLineBreak();
  knopB.waitForButton();
  Motors.initialiseer();  //initialiseert de motoren (doet niet heel veel de zumo draait naar links, naar rechts en terug naar het midden)
  lijnSensor.kalibreerAlles();
  pauzeTijd = false;
}

void loop() {
  /*
  delay(100);
  switch (xbee.leesXbee()) { //leest de xbee uit voor het volgende commando
    case 'w':
      Motors.setSnelheid(MAX_SPEED);
      break; //naar voren gaan
    case 's':
      Motors.setSnelheid(MAX_SPEED);
      Motors.Achteruit();
      break; //achteruit gaan
    case ' ':
      Motors.Stop();
      break; //stoppen (met spatiebalk)
    case 'a':
      Motors.setSnelheid(MAX_SPEED / 2);
      Motors.naarLinks();
      break; //naar links gaan
    case 'd':
      Motors.setSnelheid(MAX_SPEED / 2);
      Motors.naarRechts();
      break; //naar rechts gaan
  }
  */
  if (knopA.isPressed()) {
    pauzeTijd = true;
  }

  if (knopC.isPressed()) {
    pauzeTijd = false;
  }

  if (!pauzeTijd) {
    int lijnPositie = lijnSensor.leesPositie();
    Motors.pidController(lijnPositie);
    //lijnSensor.zietLijn();
    //xbee.printXbee(lijnSensor.zietLijn() ? "LIJN GEZIEN\n" : "LIJN NIET GEZIEN\n");
    //if (lijnPositie == -1) {
      //xbee.printXbee(String("De lijn is ") + (lijnSensor.getLijnKleur() ? "groen" : "zwart") + " en op positie " + lijnPositie);
    //}
  } else {
    Motors.Stop();
  }
}