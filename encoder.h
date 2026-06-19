#ifndef ENCODER_H
#define ENCODER_H
#include "Zumo32U4.h"

class Encoder{
public:

  Encoder();
  void init();
  int getCountsLeft();
  int getCountsRight();
  float countsToCm(int counts);
  void resetEncoders();


private:
  Zumo32U4Encoders extraEncoder;
  const int count = 910;
  const float wheel;
  const float cm;

  long countLeft;
  long countRight;
  bool initialized;
  
};
#endif