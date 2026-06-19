#ifndef XBEE_H
#define XBEE_H

#include <Zumo32U4.h>
#include <Arduino.h>

/**
 * @brief 
 * 
 */
class Xbee {
    public:
        /**
         * @brief Construeert een nieuw Xbee object.
         */
        Xbee();

        /**
         * @brief Leest de meest recente char ontvangen op de Xbee.
         * 
         * @return De ontvangen char.
         */
        char leesXbee(); //Functie definities

        /**
         * @brief Print een line break (-----) naar de Xbee serial interface (Serial1).
         */
        void printLineBreak();

        /**
         * @brief Print de meegegeven parameter als een regel naar de Xbee serial interface (Serial1).
         * @tparam T Het datatype van de te printen regel.
         * @param m De waarde of object dat geprint moet worden.
         */
        template <class T> void Xbee::printXbee(T m) {
            Serial1.println(m);
        }
};

#endif