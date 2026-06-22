#include "encoder.h"
#include <Zumo32u4Encoders.h>


Encoder::Encoder():wheel(3.0),cm((3.141592653 * wheel) / count),countLeft(0),countRight(0),initialized(false) {}

void Encoder::init() {
  extraEncoder.getCountsAndResetLeft();
  extraEncoder.getCountsAndResetRight();
}
int Encoder::getCountsLeft(){
   countLeft = extraEncoder.getCountsLeft();
    return countLeft;
}

int Encoder::getCountsRight(){
    countRight = extraEncoder.getCountsRight();
    return countRight;
}

float Encoder::countsToCm(int counts){
    return counts * cm;
}

void Encoder::resetEncoders() {
  extraEncoder.getCountsAndResetLeft();
  extraEncoder.getCountsAndResetRight();
}