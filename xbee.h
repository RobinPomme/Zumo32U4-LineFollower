#ifndef XBEE_H
#define XBEE_H

#include <Zumo32U4.h>
#include <Arduino.h>


class Xbee {
    public:
        Xbee();
        char leesXbee(); //Functie definities
        void printLineBreak();
        template <class T> void Xbee::printXbee(T m) {
            Serial1.println(m);
        }
};

#endif