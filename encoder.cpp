#include "encoder.h"
#include <Zumo32u4Encoders.h>

/**
 * @brief Constructor: initialiseert de constanten en beginwaarden.
 *
 * -  wheel   = 3.0 cm  (wieldiameter)
 * -  count   = 910   (som is 75.81 x 12 ≈ 909.7 CPR agerond 910)
 * -  cm      = (pi × wheel) / count
 * -  countLeft / countRight starten op 0
 * -  initialized start op false zodat init() eenmalig uitgevoerd wordt
 */
Encoder::Encoder():wheel(3.0),cm((3.141592653 * wheel) / count),countLeft(0),countRight(0),initialized(false) {}

/** @brief initialiseert de encoders door beide tellers te resetten naar nul */
void Encoder::init() {
  if (!initialized){
    extraEncoder.getCountsAndResetLeft();
    extraEncoder.getCountsAndResetRight();
    initialized = true;
  }
}

/** @brief leest de aantal counts van de linker encoder uit */
int Encoder::getCountsLeft(){
   countLeft = extraEncoder.getCountsLeft();
    return countLeft;
}

/** @brief leest de aantal counts van de rechter encoder uit */
int Encoder::getCountsRight(){
    countRight = extraEncoder.getCountsRight();
    return countRight;
}

/** @brief rekent de counts van de encoder om naar centimeters som is (pi x wheel) / counts */
float Encoder::countsToCm(int counts){
    return counts * cm;
}