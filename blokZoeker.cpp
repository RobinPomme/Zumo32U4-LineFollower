#include "blokZoeker.h"

BlokZoeker::BlokZoeker(ProximitySensor* p, Rijden* r):proxSensors(p),motors(r){
    this->blokGevonden = false;
}

void BlokZoeker::rijNaarMidden(){
    // Rijd 20cm naar midden
    // TODO: Daadwerkelijk 20cm rijden
    motors->Stop();
}

bool BlokZoeker::zoekBlok(){
    proxSensors->setObjectDrempelwaarde(3);
    // int objectRichting = -1;
    // TESTING! voor constante volging
    // this->blokGevonden = false;


    // Kijk of object al zichtbaar is
    while (!blokGevonden){
        switch(proxSensors->objectRichting()){
        case -1:
            // Draai naar links (default)
            motors->naarLinks();
            Serial.print("\nCase -1: Draai naar links (default)");
            break;
        case 0:
            // Break uit de while
            this->blokGevonden = true;
            Serial.print("\nCase 0: Blok gevonden!");
            motors->Stop();
            break;
        case 1:
            // Draai naar links
            motors->naarLinks();
            Serial.print("\nCase 1: Corrigeer naar links");
            break;
        case 2:
            // Draai naar rechts
            motors->naarRechts();
            Serial.print("\nCase 2: Corrigeer naar rechts");
            break;
        }
    }
    return true;
}

void BlokZoeker::duwBlok(){
    // Duw blok uit cirkel
    motors->setSnelheid(CRUISE_SPEED, CRUISE_SPEED);
    // Herhaal of blok zichtbaar is
    motors->Stop();
}