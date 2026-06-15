#include "blokZoeker.h"

BlokZoeker::BlokZoeker(ProximitySensor* p, Rijden* r, LijnSensor* l, Encoder* e):proxSensors(p),motors(r),lineSensors(l),encoder(e){
    this->blokGevonden = false;
}

void BlokZoeker::setBlokGevonden(bool status){
    this->blokGevonden = status;
}

void BlokZoeker::rijNaarMidden(){
    // Rijd 20cm naar midden
    encoder->init();
    while ((encoder->countsToCm(encoder->getCountsLeft()) <= 20) && (encoder->countsToCm(encoder->getCountsRight()) <= 20)){
        motors->setSnelheid(CRUISE_SPEED, CRUISE_SPEED);
    }
    motors->Stop();
}

bool BlokZoeker::zoekBlok(){
    proxSensors->setObjectDrempelwaarde(3);
    // int objectRichting = -1;

    // TESTING! voor constante tracking
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
    // bool borderReached = false;
    
    // Duw blok uit cirkel
    motors->setSnelheid(CRUISE_SPEED, CRUISE_SPEED);
    // zwartGedetecteerd() is private, maar lijnLijn() werkt niet voor deze doelen.
    // TODO: Andere functie gebruiken voor lijndetectie.
    while (this->lineSensors->leesPositie() = -1){
        // Blijf hierin hangen tot lijn gezien is.
        Serial.print("\nLijn niet zichtbaar");
    }
    Serial.print("\nLijn zichtbaar");
    motors->Stop();
}