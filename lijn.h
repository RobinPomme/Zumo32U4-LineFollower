#ifndef lijnh
#define lijnh

#include <Zumo32U4.h>
#include <Wire.h>
#include "xbee.h"

#define NUMSENSORS 5  ///< vertelt hoeveel sensoren de ZUMO heeft

/**
 * @brief Aangemaakt met kalibratie van een lijnkleur. Slaat de minimumwaarde, maximumwaarde, en gemiddelde waarde op.
 */
struct KalibratieData {
  int minimum[NUMSENSORS];
  int maximum[NUMSENSORS];
  int gemiddelde[NUMSENSORS];
};

/**
 * @brief Klasse voor het detecteren van lijnen met de 5 lijnsensoren op de Zumo.
 */
class LijnSensor {

public:
  /**
   * @brief Construeert een nieuw LijnSensor object.
   * 
   * @param Xbee Verwijzijng naar een Xbee object. Nodig voor logging.
   */
  LijnSensor(Xbee*);

  /**
   * @brief Kalibreert de meegegeven kleur. 
   * @details Neemt 100 meteningen met \ref getGemiddeldeMeting "getGemiddeldeMeting".
   * 
   * @param kleur De kleur die gekalibreert moet worden.
   * @return De struct KalibratieData. Deze heeft een minimum, maximum en gemiddelde waar de kleur in zou vallen.
   */
  KalibratieData kalibreer(String kleur);

  /**
   * @brief Een getter voor de variabel 'bruinGezien'.
   * 
   * @return De bool waarde van bruinGezien.
   */
  bool zagBruin();

  /**
   * @brief Roept \ref kalibreerZwart "kalibreerZwart", \ref kalibreerGroen "kalibreerGroen", en \ref kalibreerBruin "kalibreerBruin" aan.
   * 
   */
  void kalibreerAlles();

  /**
   * @brief Kalibreert de fysieke lijnsensoren via de Zumo32U4 library. Wordt alleen via de init van klasse Rijden.
   */
  void kalibreerLijn();

  /**
   * @brief Kalibreert wit zonder daarna KalibratieData aan te passen.
   */
  void kalibreerWit();

  /**
   * @brief Kalibreert zwart en slaat het op in een KalibratieData struct. Stelt de drempelwaarden in met een aangepaste foutmarge.
   * 
   */
  void kalibreerZwart();

  /**
   * @brief Kalibreert groen en slaat het op in een KalibratieData struct. Stelt de drempelwaarden in met een aangepaste foutmarge.
   */
  void kalibreerGroen();

  /**
   * @brief Kalibreert grijs en slaat het op in een KalibratieData struct. Stelt de drempelwaarden in met een aangepaste foutmarge.
   */
  void kalibreerGrijs();

  /**
   * @brief Kalibreert brijn en slaat het op in een KalibratieData struct. Stelt de drempelwaarden in met een aangepaste foutmarge.
   */
  void kalibreerBruin();

  /**
   * @brief Controleert op alle lijnkleuren en berekent een gewogen gemiddelde.
   * 
   * @return Een gewogen gemiddelde van de sensorlezingen tussen 1000 en 5000.
   */
  int leesPositie();

  /**
   * @brief Een getter voor de waarde van groeneLijn.
   * 
   * @return De boolean waarde van groeneLijn.
   */
  bool getLijnKleur(); // TODO: Naam aanpassen.

  /**
   * @brief Voert drie getGemiddeldeMetingen uit en geeft de waarde van zwartGedetecteerd op deze waardes terug.
   * 
   * @return De boolean waarde van \ref zwartgedetecteerd "zwartGedetecteerd".
   */
  bool getZwartGezien();
  void resetBruin();

  /**
   * @brief Zet boolean variabel bruinGezien op false.
   */
  void resetBruin();

private:
  /**
   * @brief Bouwt de struct kalibratiedata.
   * 
   * @return De struct KalibratieData.
   */
  KalibratieData getGemiddeldeMeting(int);

  /**
   * @brief Controleert of de gemiddelde waarde van de gegeven KalibratieData binnen of op de drempelwaardes van zwart valt.
   * 
   * @return True als het gemiddelde binnen of op de drempelwaardes valt. False als het gemiddelde erbuiten valt.
   */
  bool zwartGedetecteerd(KalibratieData);

  /**
   * @brief Controleert of de gemiddelde waarde van de gegeven KalibratieData binnen of op de drempelwaardes van groen valt.
   * 
   * @return True als het gemiddelde binnen of op de drempelwaardes valt. False als het gemiddelde erbuiten valt.
   */
  bool groenGedetecteerd(KalibratieData);

  /**
   * @brief Controleert of de gemiddelde waarde van de gegeven KalibratieData binnen of op de drempelwaardes van bruin valt.
   * 
   * @return True als het gemiddelde binnen of op de drempelwaardes valt. False als het gemiddelde erbuiten valt.
   */
  bool bruinGedetecteerd(KalibratieData);

  /**
   * @brief Controleert of de gemiddelde waarde van de gegeven KalibratieData binnen of op de drempelwaardes van grijs valt.
   * 
   * @return True als het gemiddelde binnen of op de drempelwaardes valt. False als het gemiddelde erbuiten valt.
   */
  bool grijsGedetecteerd(KalibratieData);

  bool groeneLijn;
  bool volgendeLinks;
  bool volgendeRechts;
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