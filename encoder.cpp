#include "encoder.h"
#include <Zumo32u4Encoders.h>


Encoder::Encoder():wheel(3.9),cm((3.141592653 * wheel) / count),countLeft(0),countRight(0),initialized(false) {}

void Encoder::init() {
  if (!initialized){
    superCooleExtraToffeEncodersVanZumoOfzo.getCountsAndResetLeft();
    superCooleExtraToffeEncodersVanZumoOfzo.getCountsAndResetRight();
    initialized = true;
  }
}
int Encoder::getCountsLeft(){
    countLeft = superCooleExtraToffeEncodersVanZumoOfzo.getCountsAndResetLeft();
    return countLeft;
}

int Encoder::getCountsRight(){
    countRight = superCooleExtraToffeEncodersVanZumoOfzo.getCountsAndResetRight();
    return countRight;
}

float Encoder::countsToCm(int counts){
    return counts * cm;
}

