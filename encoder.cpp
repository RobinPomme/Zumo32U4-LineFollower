#include "encoder.h"
#include <Zumo32u4Encoders.h>

const float Encoder::wheel = 3.9f;
const float Encoder::cm =(3.14159f * wheel) / count;

int Encoder::countLeft = 0;
int Encoder::countRight = 0;
bool Encoder::initialized = false;



void Encoder::init() {
  if (!initialized){
    Encoder::init();
    initialized = true;
  }
}
int Encoder::getCountsLeft(){
    countLeft += Zumo32U4Encoders::getCountsAndResetLeft();
    return countLeft;
}

int Encoder::getCountsRight(){
    countRight += Zumo32U4Encoders::getCountsAndResetRight();
    return countRight;
}

float Encoder::countsToCm(int counts){
    return counts * cm;
}

