#include "lijn.h"
#include "xbee.h"

/**
 * @brief initialliseert de 5 sensoren van de ZUMO
 */
LijnSensor::LijnSensor(Xbee* x)
  : xbeePointer(x), groeneLijn(false),bruinGezien(false),laatsteLijn(3000) {
  sensoren.initFiveSensors();
}

bool LijnSensor::getZwartGezien() {
  KalibratieData meting = getGemiddeldeMeting(3);
  return zwartGedetecteerd(meting);
}

KalibratieData LijnSensor::getGemiddeldeMeting(int aantalMetingen) {
  KalibratieData resultaat;

  sensoren.readCalibrated(waarden);

  unsigned long totaal[NUMSENSORS];

  for (int i = 0; i < NUMSENSORS; i++) {
    totaal[i] = waarden[i];
    resultaat.minimum[i] = waarden[i];
    resultaat.maximum[i] = waarden[i];
  }
  for (int i = 0; i < aantalMetingen; i++) {
    sensoren.readCalibrated(waarden);
    for (int j = 0; j < NUMSENSORS; j++) {
      totaal[j] += waarden[j];
      if (waarden[j] < resultaat.minimum[j]) {
        resultaat.minimum[j] = waarden[j];
      }
      if (waarden[j] > resultaat.maximum[j]) {
        resultaat.maximum[j] = waarden[j];
      }
    }
  }
  for (int i = 0; i < NUMSENSORS; i++) {
    resultaat.gemiddelde[i] = totaal[i] / (aantalMetingen + 1);
  }
  return resultaat;
}
/**
 * @brief kalibreert de ZUMO zodat het de lijn kan zien
 */
KalibratieData LijnSensor::kalibreer(String kleur) {
  xbeePointer->printLineBreak();
  xbeePointer->printXbee("Kleur " + kleur + " wordt nu gekalibreert.");
  knopB.waitForButton();
  xbeePointer->printLineBreak();
  KalibratieData resultaat = getGemiddeldeMeting(100);

  String minString = "Minimum waarde ";
  String maxString = "Maximum waarde ";
  String gemString = "Gemiddelde waarde ";
  for (int i = 0; i < NUMSENSORS; i++) {
    minString += resultaat.minimum[i];
    minString += " ";
    maxString += resultaat.maximum[i];
    maxString += " ";
    gemString += resultaat.gemiddelde[i];
    gemString += " ";
  }
  xbeePointer->printXbee(minString);
  xbeePointer->printXbee(maxString);
  xbeePointer->printXbee(gemString);

  return resultaat;
}

/*
int LijnSensor::leesLijnPositieTest() {
  return sensoren.readLine(waarden) + 1000;
}
*/
/**
 * @brief geeft de positie van de lijn
 */
int LijnSensor::leesPositie() {
  KalibratieData laatsteMeting = getGemiddeldeMeting(1);

  long totaal = 0;
  long gewogenGemiddelde = 0;
  bool lijnGezien = false;

  groeneLijn = false;


  for(int i = 0; i<NUMSENSORS; i++) {
    int meting = laatsteMeting.gemiddelde[i];

    bool zietZwart = (meting >= drempelwaardenZwart.minimum[i] && meting <= drempelwaardenZwart.maximum[i]);
    bool zietGroen = (meting >= drempelwaardenGroen.minimum[i] && meting <= drempelwaardenGroen.maximum[i]);

    if (zietZwart || zietGroen) {

      int gewicht = meting;


      if (zietGroen) {
        groeneLijn = true;

        if (i == 0 || i == 4) {
          gewicht = meting * 6;
        }
      }

      totaal += gewicht;
      gewogenGemiddelde += (long)gewicht * ((i + 1) * 1000L);
      lijnGezien = true;
    }
  }

    if (!lijnGezien || totaal <= 0) {
      return -1;
    }

    laatsteLijn = gewogenGemiddelde / totaal;
    return laatsteLijn;
  //bruinGezien = bruinGedetecteerd(laatsteMeting);
  /*
  if (groenGedetecteerd(laatsteMeting)) {
    long totaal = 0;
    long gewogenGemiddelde = 0;
    for (int i = 0; i < NUMSENSORS; i++) {
      if (laatsteMeting.gemiddelde[i] <= drempelwaardenGroen.maximum[i] && laatsteMeting.gemiddelde[i] >= drempelwaardenGroen.minimum[i]) {
        totaal += laatsteMeting.gemiddelde[i];
        gewogenGemiddelde += (long)laatsteMeting.gemiddelde[i] * ((i + 1) * 1000L);
      }
    }
    if (totaal <= 0) {
      return -1;
    }
    laatsteLijn = gewogenGemiddelde / totaal;
    return laatsteLijn;
  } else if (zwartGedetecteerd(laatsteMeting)) {
    long totaal = 0;
    long gewogenGemiddelde = 0;
    for (int i = 0; i < NUMSENSORS; i++) {
      totaal += laatsteMeting.gemiddelde[i];
      gewogenGemiddelde += (long)laatsteMeting.gemiddelde[i] * ((i + 1) * 1000L);
    }
    if (totaal <= 0) {
      return -1;
    }
    laatsteLijn = gewogenGemiddelde / totaal;
    return laatsteLijn;
  }
  return laatsteLijn;
  */
}
/**
 * @brief geeft true terug als die een lijn ziet
 */
/*
bool LijnSensor::zietLijn() {
  bool zwartGezien = false;
  bool groenGezien = false;

  sensoren.readCalibrated(waarden);
  xbeePointer->printLineBreak();
  for (int i = 0; i < NUMSENSORS; i++) {
    if (waarden[i] >= drempelwaardenZwart.minimum[i] && waarden[i] <= drempelwaardenZwart.maximum[i]) {
      String test = String(i) + " ziet lijn en heeft waarde " + String(waarden[i]) + " en drempelwaarde is min " + String(drempelwaardenZwart.minimum[i]) + " max " + String(drempelwaardenZwart.maximum[i]);
      xbeePointer->printXbee(test);
      zwartGezien = true;
      continue;
    }
    String test = String(i) + " ziet lijn NIET en heeft waarde " + String(waarden[i]) + " en drempelwaarde is min " + String(drempelwaardenZwart.minimum[i]) + " max " + String(drempelwaardenZwart.maximum[i]);
    xbeePointer->printXbee(test);
  }
  xbeePointer->printLineBreak();
  return zwartGezien || groenGezien;
}
*/

void LijnSensor::kalibreerWit() {
  kalibreer("wit");
  //sensoren.calibrate();
}

void LijnSensor::kalibreerZwart() {
  //KalibratieData zwarteData = kalibreer("zwart");
  for (int i = 0; i < NUMSENSORS; i++) {
    drempelwaardenZwart.minimum[i] = 250;//zwarteData.minimum[i] * 0.3;
    drempelwaardenZwart.maximum[i] = 1500;//zwarteData.maximum[i] * 1.5;
    drempelwaardenZwart.gemiddelde[i] = 1000;//zwarteData.gemiddelde[i];
  }
}

void LijnSensor::kalibreerGroen() {
  KalibratieData groeneData = kalibreer("groen");
  for (int i = 0; i < NUMSENSORS; i++) {
    drempelwaardenGroen.minimum[i] = groeneData.minimum[i] * 0.7;
    drempelwaardenGroen.maximum[i] = groeneData.maximum[i] * 1.1;
    drempelwaardenGroen.gemiddelde[i] = groeneData.gemiddelde[i];
  }
}

void LijnSensor::kalibreerBruin() {
  KalibratieData bruineData = kalibreer("bruin");
  for (int i = 0; i < NUMSENSORS; i++) {
    drempelwaardenBruin.minimum[i] = bruineData.minimum[i] * 0.975;
    drempelwaardenBruin.maximum[i] = bruineData.maximum[i] * 1.025;
    drempelwaardenBruin.gemiddelde[i] = bruineData.gemiddelde[i];
  }
}

void LijnSensor::kalibreerGrijs() {
  KalibratieData grijzeData = kalibreer("grijs");
  for (int i = 0; i < NUMSENSORS; i++) {
    drempelwaardenGrijs.minimum[i] = grijzeData.minimum[i] * 0.6;
    drempelwaardenGrijs.maximum[i] = grijzeData.maximum[i] * 1.4;
    drempelwaardenGrijs.gemiddelde[i] = grijzeData.gemiddelde[i];
  }
}

void LijnSensor::kalibreerAlles() {
  //kalibreerWit();
  kalibreerZwart();
  kalibreerGroen();
  //kalibreerGrijs();
  //kalibreerBruin();
  xbeePointer->printLineBreak();
}

void LijnSensor::kalibreerLijn() {
  sensoren.calibrate();
}

bool LijnSensor::groenGedetecteerd(KalibratieData meting) {
  for (int i = 0; i < NUMSENSORS; i++) {
    if (meting.gemiddelde[i] <= drempelwaardenGroen.maximum[i] && meting.gemiddelde[i] >= drempelwaardenGroen.minimum[i]) {
      xbeePointer->printXbee("Groene lijn sensor " + String(i) + " meting: " + meting.gemiddelde[i] + " min: " + drempelwaardenGroen.minimum[i] + " max: " + drempelwaardenGroen.maximum[i]);
      return true;
    }
  }
  return false;
}

bool LijnSensor::zwartGedetecteerd(KalibratieData meting) {
  for (int i = 0; i < NUMSENSORS; i++) {
    if (meting.gemiddelde[i] <= drempelwaardenZwart.maximum[i] && meting.gemiddelde[i] >= drempelwaardenZwart.minimum[i]) {
      groeneLijn = false;
      return true;
    }
  }
  return false;
}

bool LijnSensor::bruinGedetecteerd(KalibratieData meting) {
  bool bruinNietGezien = false;
  for (int i = 0; i < NUMSENSORS; i++) {
    if (meting.gemiddelde[i] <= drempelwaardenBruin.maximum[i] && meting.gemiddelde[i] >= drempelwaardenBruin.minimum[i]) {
    } else {
      bruinNietGezien = true;
    }
  }
  if (!bruinNietGezien) {
    xbeePointer->printXbee("Bruin gezien!");
  }
  return !bruinNietGezien;
}

bool LijnSensor::grijsGedetecteerd(KalibratieData meting) {
  grijsLinks = false;
  grijsRechts = false;
  if (meting.gemiddelde[0] <= drempelwaardenGrijs.maximum[0] && meting.gemiddelde[0] >= drempelwaardenGrijs.minimum[0]) {
    xbeePointer->printXbee("Grijs links gezien!");
    grijsLinks = true;
  }
  if (meting.gemiddelde[4] <= drempelwaardenGrijs.maximum[4] && meting.gemiddelde[4] >= drempelwaardenGrijs.minimum[4]) {
    xbeePointer->printXbee("Grijs rechts gezien!");
    grijsRechts = true;
  }
  return grijsLinks && grijsRechts;
}

bool LijnSensor::getLijnKleur() {
  return groeneLijn;
}

bool LijnSensor::zagBruin() {
  return bruinGezien;
}
