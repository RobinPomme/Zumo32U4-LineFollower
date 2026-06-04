#include "xbee.h"

Xbee::Xbee() {
    Serial1.begin(9600); //start serial communication via de XBee
}

char Xbee::leesXbee() {
    return Serial1.read(); //leest de XBee af
}

void Xbee::printXbee(String m) {
    Serial1.println(m);
}

void Xbee::printXbee(int m) {
    Serial1.println(m);
}

void Xbee::printLineBreak() {
    printXbee("------------------------------------------");
}