#ifndef XBEE_H
#define XBEE_H

#include <Zumo32U4.h>
#include <Arduino.h>


class Xbee {
    public:
        Xbee();
        char leesXbee(); //Functie definities
        void printXbee(String meegegevenwaarde);
        void printXbee(int meegegevenwaarde);
        void printLineBreak();
};

#endif