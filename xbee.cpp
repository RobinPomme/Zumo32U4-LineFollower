#include "xbee.h"

Xbee::Xbee() {
    Serial1.begin(9600); //start serial communication via de XBee
}

char Xbee::leesXbee() {
    return Serial1.read(); //leest de XBee af
}

void Xbee::printLineBreak() {
    printXbee("----------------------------------------------------------------------");
}