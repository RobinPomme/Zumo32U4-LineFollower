#include "rijden.h"

Rijden::Rijden(Xbee* x, LijnSensor* l)
  : lineSensors(l), xbeePointer(x), afgeleide(0), integraal(0) {
  snelheid[0] = 0;
  snelheid[1] = 0;
  for (int i = 0; i<BUFFER_COUNT; i++) {
    resetBuffer[i] = false;
  }
}  //constructor voor de zumo die de snelheid meteen op 0 zet

int Rijden::getSnelheid() const {
  return snelheid;  //geeft de snelheid als de gebruiker erom vraagt
}

void Rijden::initialiseer() {
  setSnelheid(CALIBRATE_SPEED);
  lineSensors->kalibreerLijn();
  for (int i = 0; i < 200; i++) {
    delay(20);
    lineSensors->kalibreerLijn();
    if (i >= 50 && i <= 150) {
      setSnelheid(-1 * CALIBRATE_SPEED, CALIBRATE_SPEED);
    } else {
      setSnelheid(CALIBRATE_SPEED, -1 * CALIBRATE_SPEED);
    }
  }
  Stop();  //de zumo draait naar links, naar rechts en weer terug naar het midden
  lineSensors->kalibreerAlles();
}

void Rijden::setSnelheid(int nieuweSnelheid) {
  snelheid[0] = nieuweSnelheid;
  snelheid[1] = nieuweSnelheid;
  motorenVanZumo.setSpeeds(nieuweSnelheid, nieuweSnelheid);  //verandert de snelheid van de zumo
}

void Rijden::setSnelheid(int l, int r) {
  snelheid[0] = l;
  snelheid[1] = r;
  motorenVanZumo.setSpeeds(l, r);
}

void Rijden::naarLinks() {
  setSnelheid(-1 * CRUISE_SPEED, CRUISE_SPEED);  //maakt de snelheid van de linker motor negatief zodat de zumo naar links draait
}

void Rijden::naarRechts() {
  motorenVanZumo.setSpeeds(CRUISE_SPEED, -1 * CRUISE_SPEED);  //maakt de snelheid van de rechter motor negatief zodat de zumo naar rechts draait
}

void Rijden::Stop() {
  snelheid[0] = 0;
  snelheid[1] = 0;
  motorenVanZumo.setSpeeds(snelheid[0], snelheid[1]);  //zet de snelheid van de zumo op 0
}

void Rijden::Achteruit() {
  snelheid[0] *= -1;
  snelheid[1] *= -1;
  motorenVanZumo.setSpeeds(snelheid[0], snelheid[1]);  //maakt bijde motoren dezelfde snelheid alleen dan negatief
}

void Rijden::pidController(int lijnPositie) {
  if (lijnPositie == -1) {
    bool bufferVol = true;
    for(int i = 0; i<BUFFER_COUNT; i++) {
      if(resetBuffer[i] == true) {
        resetBuffer[i] = false;
        bufferVol = false;
        break;
      }
    }
    if (!bufferVol) {
      return;
    }
    lijnPositie = 3000;
    afgeleide = 0;
    xbeePointer->printXbee("BUFFER VOL!!!! we gaan nu rechtdoor.");
  } else {
    for (int i = 0; i<BUFFER_COUNT; i++) {
      resetBuffer[i] = true;
    }
  }

  error = 3000 - lijnPositie;

  double Yp = CONSTANT_P * error;

  integraal += error;
  double Yi = integraal * CONSTANT_I;

  double Yd = (error - afgeleide) * CONSTANT_D;
  afgeleide = error;

  int output = Yp + Yi + Yd;

  int snelheid = lineSensors->getLijnKleur() ? CRUISE_SPEED / 2 : CRUISE_SPEED;

  int leftSpeed = constrain(snelheid - output, -1 * MAX_SPEED, MAX_SPEED);
  int rightSpeed = constrain(snelheid + output, -1 * MAX_SPEED, MAX_SPEED);

  setSnelheid(leftSpeed, rightSpeed);
}