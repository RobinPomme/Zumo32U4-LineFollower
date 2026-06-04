#ifndef PROXIMITY_H
#define PROXIMITY_H

#include <Wire.h>
#include <Zumo32U4.h>
#include "xbee.h"

/**
 * \brief Klasse voor het beheer van de proximity sensoren op de Zumo32U4.
 *
 * Deze klasse geeft functionaliteit om proximity sensoren te initialiseren, waarden te lezen en objectafstanden te lezen.
 */
class ProximitySensor {
public:

    /** \brief Constructor voor ProximitySensor. */
    ProximitySensor(Xbee*);

    /**
     * \brief Controleert of een object zichtbaar is.
     * \return true als een object gedetecteerd wordt, anders false.
     */
    bool objectVisible();

    // /**
    //  * \brief Controleert of een object zichtbaar is.
    //  * \return true als een object gedetecteerd wordt, anders false.
    //  */
    // bool objectVisibleLeft();

    // /**
    //  * \brief Controleert of een object zichtbaar is.
    //  * \return true als een object gedetecteerd wordt, anders false.
    //  */
    // bool objectVisibleRight();

    /**
     * \brief Stelt de drempelwaarde voor object detectie in.
     * \param threshold De nieuwe drempelwaarde.
     */
    void setObjectThreshold(int threshold);

    void printReadings() const;

private:
    Zumo32U4ProximitySensors zumoProxSensors;
    static const int defaultObjectThreshold = 1;
    int objectThreshold;
    Xbee* xbee;
};

#endif // PROXIMITY_H
