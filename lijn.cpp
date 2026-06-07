#include "lijn.h"
#include "xbee.h"

/**
 * @brief initialliseert de 5 sensoren van de ZUMO
 */
LijnSensor::LijnSensor(Xbee* x):xbeePointer(x) {
  sensoren.initFiveSensors();
}
/**
 * @brief kalibreert de ZUMO zodat het de lijn kan zien
 */
KalibratieData LijnSensor::kalibreer(String kleur){
  KalibratieData resultaat;
  xbeePointer->printLineBreak();
  xbeePointer->printXbee("Kleur " + kleur + " wordt nu gekalibreert.");
  knopB.waitForButton();
  xbeePointer->printLineBreak();
  sensoren.readCalibrated(waarden);
  unsigned long totaal[NUMSENSORS];
  for (int i = 0; i<NUMSENSORS; i++) {
    resultaat.minimum[i] = waarden[i];
    resultaat.maximum[i] = waarden[i];
    resultaat.gemiddelde[i] = waarden[i];
    totaal[i] = waarden[i];
  }
  for (int i = 0; i<100; i++) {
    sensoren.readCalibrated(waarden);
    for (int j = 0; j<NUMSENSORS; j++) {
      totaal[j] += waarden[j];
      if (waarden[j] < resultaat.minimum[j]) {
        resultaat.minimum[j] = waarden[j];
      }
      if (waarden[j] > resultaat.maximum[j]) {
        resultaat.maximum[j] = waarden[j];
      }
    }
  }

  String minString = "Minimum waarde ";
  String maxString = "Maximum waarde ";
  String gemString = "Gemiddelde waarde ";
  for (int i = 0; i<NUMSENSORS; i++) {
    resultaat.gemiddelde[i] = totaal[i] / 101;
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
/**
 * @brief geeft de positie van de lijn
 */
  int LijnSensor::leesPositie() {
    int test = sensoren.readLine(waarden);
    xbeePointer->printXbee(test);
    return test;
  }
/**
 * @brief geeft true terug als die een lijn ziet
 */
  bool LijnSensor::zietLijn(){
    bool zwartGezien = false;
    bool groenGezien = false;

    sensoren.readCalibrated(waarden);
    xbeePointer->printLineBreak();
    for (int i = 0; i< NUMSENSORS; i++) {
      if (waarden[i] > drempelwaardenZwart.minimum[i] && waarden[i] < drempelwaardenZwart.maximum[i]) {
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

  void LijnSensor::kalibreerWit() {
    kalibreer("wit");
    sensoren.calibrate();
  }

  void LijnSensor::kalibreerZwart() {
    KalibratieData zwarteData =  kalibreer("zwart");
    for (int i = 0; i< NUMSENSORS; i++) {
      drempelwaardenZwart.minimum[i] = zwarteData.minimum[i] / 2.15;
      drempelwaardenZwart.maximum[i] = zwarteData.maximum[i];
      drempelwaardenZwart.gemiddelde[i] = zwarteData.gemiddelde[i];
    }
  }

  void LijnSensor::kalibreerGroen() {
    kalibreer("groen");
  }

  void LijnSensor::kalibreerBruin() {
    kalibreer("bruin");
  }

  void LijnSensor::kalibreerGrijs() {
    kalibreer("grijs");
  }

  void LijnSensor::kalibreerAlles() {
    kalibreerWit();
    kalibreerZwart();
    kalibreerGroen();
    kalibreerGrijs();
    kalibreerBruin();
    xbeePointer->printLineBreak();
  }

  void LijnSensor::kalibreerLijn() {
    sensoren.calibrate();
  }