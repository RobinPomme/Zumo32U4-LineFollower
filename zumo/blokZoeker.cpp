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
    proxSensors->setObjectDrempelwaarde(5);
    // int objectRichting = -1;

    // TESTING! voor constante tracking
    // this->blokGevonden = false;


    // Kijk of object al zichtbaar is
    while (!blokGevonden){
        switch(proxSensors->objectRichting()){
        case -1:
            // Draai naar links (default)
            motors->naarLinks();
            Serial1.println("Case -1: Draai naar links (default)");
            break;
        case 0:
            // Break uit de while
            this->blokGevonden = true;
            Serial1.println("Case 0: Blok gevonden!");
            motors->Stop();
            break;
        case 1:
            // Draai naar links
            motors->naarLinks();
            Serial1.println("Case 1: Corrigeer naar links");
            break;
        case 2:
            // Draai naar rechts
            motors->naarRechts();
            Serial1.println("Case 2: Corrigeer naar rechts");
            break;
        }
    }
    return true;
}

void BlokZoeker::duwBlok(Xbee* xb){
    bool zwartGezien = false;
    
    // Duw blok uit cirkel
    motors->setSnelheid(CRUISE_SPEED, CRUISE_SPEED);

    while (!zwartGezien){
        // Blijf hierin hangen tot lijn gezien is.
        zwartGezien = lineSensors->getZwartGezien();

        Serial1.println("Lijn niet zichtbaar");
    }

    Serial1.println("Lijn zichtbaar");
    motors->Stop();
}