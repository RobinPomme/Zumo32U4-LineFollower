#ifndef ENCODER_H
#define ENCODER_H
#include "Zumo32U4.h"

class Encoder{
public:


  static void init();
  static int getCountsLeft();
  static int getCountsRight();
  static float countsToCm(int counts);


private:
  static const int count = 910;
  static const float wheel;
  static const float cm;

  static int countLeft;
  static int countRight;
  static bool initialized;

};
#endif