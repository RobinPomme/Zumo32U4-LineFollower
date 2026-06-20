#ifndef RIJDEN_H
#define RIJDEN_H

#include <Zumo32U4.h>
#include "lijn.h"

#define MAX_SPEED 400
#define CRUISE_SPEED 300
#define CALIBRATE_SPEED 200

#define CONSTANT_P 0.75
#define CONSTANT_I 0
#define CONSTANT_D 1.1 //dit zijn nu mooie waarden (Kp = 0.75, Ki = 0, Kd = 1.1 met snelheid = 300 en max in pid = max_speed (400))

#define BUFFER_COUNT 6

/**
 * @brief Klasse voor het aansturen van de snelheid en richting van de Zumo motoren.
 */
class Rijden {
  private:
    bool resetBuffer[BUFFER_COUNT];
    int snelheid[2]; //een variabele om de snelheid bij te houden
    int richting; //een variabele om de richting in op te slaan
    int error;
    int afgeleide;
    long integraal;
    Zumo32U4Motors motorenVanZumo; //maakt een nieuw object voor de motoren van de zumo
    LijnSensor* lineSensors;
    Xbee* xbeePointer;
  public:
    /**
     * @brief Construeert een nieuw Rijden object.
     * 
     * @param Xbee Een verwijzing naar een Xbee object. Nodig voor logging.
     * @param Lijnsensor Een verwijzing naar een LijnSensor object. Nodig voor het initialisatieproces en voor het aansturen van de motoren met de PID-controller.
     */
    Rijden(Xbee*, LijnSensor*);

    /**
     * @brief Een getter voor snelheid.
     * 
     * @return De int waarde van snelheid. Waarde van -400 t/m 400.
     */
    int getSnelheid() const;

    /**
     * @brief Een setter voor het variabel snelheid.
     * 
     * @param snelheid De snelheid voor beide motoren. Waarde van -400 t/m 400, negatieve waarde draait de motoren achteruit.
     */
    void setSnelheid(int snelheid);

    /**
     * @brief Een setter voor het variabel snelheid.
     * 
     * @param snelheidL De snelheid voor de linker motor. Waarde van -400 t/m 400, negatieve waarde draait de motor achteruit.
     * @param snelheidR De nelheid voor de rechter motor. Waarde van -400 t/m 400, negatieve waarde draait de motor achteruit.
     */
    void setSnelheid(int snelheidL, int snelheidR);

    /**
     * @brief 
     * 
     */
    void initialiseer();

    /**
     * @brief Zet de snelheid van de linker motoren op 'CRUISE_SPEED * -1', en de snelheid van de rechter motoren op 'CRUISE_SPEED'.
     */
    void naarLinks();

    /**
     * @brief Zet de snelheid van de linker motoren op 'CRUISE_SPEED', en de snelheid van de rechter motoren op 'CRUISE_SPEED * -1'.
     */
    void naarRechts();

    /**
     * @brief Neemt de huidige snelheidswaarde van beide motoren en vermenigvuldigd dit maal -1. Hierdoor zullen de motoren dezelfde snelheid draaien, maar dan achteruit.
     */
    void Achteruit();

  /**
   * @brief Berekent en voert de PID-correctie uit voor het volgen van een lijn.
   * @details Deze functie regelt de motorsnelheden op basis van de afwijking ten opzichte van de gewenste lijnpositie.
   * Als de lijn niet zichtbaar is, gaat er een buffersysteem in werking om de huidige koers aan te houden. Als de buffer vol is zal de zumo standaard rechtdoor gaan rijden.
   * 
   * @param lijnPositie De gemeten positie van de lijn. De waarde -1 laat weten dat de sensoren geen lijn hebben gedetecteerd.
   */
    void pidController(int lijnPositie);

    /**
     * @brief Zet de snelheidswaarde van beide moteren op 0.
     */
    void Stop(); //functie definities
};

#endif