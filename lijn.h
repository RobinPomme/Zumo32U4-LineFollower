#ifndef lijnh
#define lijnh

#include <Zumo32U4.h>
#include <Wire.h>
#include "xbee.h"

#define NUMSENSORS 5  ///< vertelt hoeveel sensoren de ZUMO heeft

struct KalibratieData {
  int minimum[NUMSENSORS];
  int maximum[NUMSENSORS];
  int gemiddelde[NUMSENSORS];
};

/// @brief maakt de class aan
class LijnSensor {

public:
  LijnSensor(Xbee*);
  KalibratieData kalibreer(String kleur);  ///< kalibreert de sensoren
  bool zagBruin();
  void kalibreerAlles();
  void kalibreerLijn();
  void kalibreerWit();
  void kalibreerZwart();
  void kalibreerGroen();
  void kalibreerGrijs();
  void kalibreerBruin();
  int leesPositie();                 ///< geeft de positie van de lijn
  int leesPositieZwart();
  bool getLijnKleur();
  bool getZwartGezien();
  void resetBruin();

private:
  KalibratieData getGemiddeldeMeting(int);
  bool zwartGedetecteerd(KalibratieData);
  bool groenGedetecteerd(KalibratieData);
  bool bruinGedetecteerd(KalibratieData);
  bool grijsGedetecteerd(KalibratieData);
  bool groeneLijn;
  bool grijsLinks;
  bool grijsRechts;
  bool bruinGezien;
  int laatsteLijn;
  Zumo32U4LineSensors sensoren;
  unsigned int waarden[NUMSENSORS];  ///< hier wordt de array van de sensor waarden in
  KalibratieData drempelwaardenZwart;
  KalibratieData drempelwaardenGroen;
  KalibratieData drempelwaardenGrijs;
  KalibratieData drempelwaardenBruin;
  Xbee* xbeePointer;
  Zumo32U4ButtonB knopB;
};

#endif