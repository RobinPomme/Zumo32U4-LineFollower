#ifndef PROXIMITY_H
#define PROXIMITY_H

#include <Wire.h>
#include <Zumo32U4.h>
#include "xbee.h"

/**
 * @brief Klasse voor het beheer van de proximity sensoren op de Zumo32U4.
 *
 * Deze klasse geeft functionaliteit om proximity sensoren te initialiseren, waarden te lezen en objectafstanden te lezen.
 */
class ProximitySensor {
public:

    /** \brief Construeert een ProximitySensor object. */
    ProximitySensor(Xbee*);

    /**
     * @brief Controleert of een object zichtbaar is.
     * @return true als een object gedetecteerd wordt, anders false.
     */
    bool objectZichtbaar();

    /**
     * @brief Berekent de ligging van het object, als een object zichtbaar is.
     * 
     * @return -1 = Geen object zicthbaar
     * @return 0 = Beide L & R gelijke waarde
     * @return 1 = Links
     * @return 2 = Rechts
     * @return Default = 0
     */
    int objectRichting();

    /**
     * @brief Stelt de drempelwaarde voor object detectie in.
     * @param threshold De nieuwe drempelwaarde.
     */
    void setObjectDrempelwaarde(int threshold);

    /**
     * @brief Print lezingen van zowel de linker als rechter LED, en of een object zichtbaar is.
     */
    void printAlles() const;

private:
    Zumo32U4ProximitySensors zumoProxSensors;
    static const int defaultObjectDrempelwaarde = 1;
    int objectDrempelwaarde;
    Xbee* xbee;
};

#endif // PROXIMITY_H
