#include "blokZoeker.h"

BlokZoeker::BlokZoeker(ProximitySensor* p, Rijden* r):proxSensors(p),motors(r){
    this->blokGevonden = false;
}

void BlokZoeker::rijNaarMidden(){
    // Rijd 20cm naar midden
    // TODO: Daadwerkelijk 20cm rijden
    motors->Stop();
}

void BlokZoeker::zoekBlok(){
    proxSensors->setObjectDrempelwaarde(3);
    // int objectRichting = -1;

    // Kijk of object al zichtbaar is
    while (!blokGevonden){
        switch(proxSensors->objectRichting()){
        case -1:
            // Draai naar links (default)
            motors->naarLinks();
            break;
        case 0:
            // Break uit de while
            this->blokGevonden = true;
            motors->Stop();
            break;
        case 1:
            // Draai naar links
            motors->naarLinks();
            break;
        case 2:
            // Draai naar rechts
            motors->naarRechts();
            break;
        }
    }
    return; // true
}

void BlokZoeker::duwBlok(){
    // Duw blok uit cirkel
    motors->setSnelheid(CRUISE_SPEED, CRUISE_SPEED);
    // Herhaal of blok zichtbaar is
    motors->Stop();
}