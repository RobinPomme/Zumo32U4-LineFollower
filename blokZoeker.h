#ifndef BLOKZOEKER_H
#define BLOKZOEKER_H

#include <Wire.h>
#include <Zumo32U4.h>
#include "proximity.h"
#include "rijden.h"
#include "lijn.h"
#include "encoder.h"

#define ZWARTBUFFER 10

/**
 * @brief Klasse voor het zoeken en duwen van een blokje, of een ander object. Maakt gebruik van de proximity sensoren om een 
 */
class BlokZoeker {
public:
    /**
     * @brief Construeert een nieuw BlokZoeker object.
     * 
     * @param p Verwijzijng naar een ProximitySensor object. Nodig voor het detecteren van het blokje.
     * @param r Verwijzijng naar een Rijden object. Nodig voor het aansturen van de motoren.
     * @param l Verwijzijng naar een LijnSensor object. Nodig voor het detecteren van de rand van de cirkel.
     * @param e Verwijzijng naar een Encoder object. Nodig voor het bijhouden van afstand voor de 20cm vooruit rijden in \ref rijNaarMidden "rijNaarMidden".
     */
    BlokZoeker(ProximitySensor*, Rijden*, LijnSensor*, Encoder*);

    /**
     * @brief Zoekt het blokje door te draaien totdat de proximitysensoren iets detecteren. Draait standaard naar links.
     * @details De functie kijkt eerst of het blokje al zichtbaar is. Als het blokje zichtbaar is, maar niet gedetecteerd wordt door beide sensoren, dan zal de zumo zichzelf corrigeren door de juiste richt op te draaien.
     * Als er geen blokje zichtbaar is zal de zumo standaard naar links draaien.
     * 
     * Wanneer beide sensoren het blokje zien wordt blokGevonden true gemaakt door \ref setBlokGevonden "setBlokGevonden". Hierdoor stopt de while loop en wordt de 'return true;' bereikt.
     * 
     * @return Returnt true als een blok is gevonden. Set ook blokGevonden naar true via \ref setBlokGevonden "setBlokGevonden".
     */
    bool zoekBlok();

    /**
     * @brief Stuurt de motors aan om 20cm naar voren te rijden. Meet afgelegde afstand door middel van de encoders.
     * @details Deze functie moet als eerste worden aangeroepen na het detecteren van de bruine lijn. Rijd naar voren totdat beide encoders links en rechts 20cm of meer gemeten hebben.
     */
    void rijNaarMidden();

    /**
     * @brief Stuurt de motors aan om rechtdoor te rijden totdat een zwarte lijn gezien is met \ref getZwartGezien "getZwartGezien".
     * 
     * @param xb Een verwijzing naar een Xbee oobject. Gebruikt voor logging.
     */
    void duwBlok(Xbee*);

    /**
     * @brief Set status van private variabel blokGevonden.
     * 
     * @param status De nieuwe status van blokGevonden.
     */
    void setBlokGevonden(bool);
private:
    ProximitySensor* proxSensors;
    Rijden* motors;
    LijnSensor* lineSensors;
    Encoder* encoder;
    bool blokGevonden;
};

#endif // BLOKZOEKER_H
