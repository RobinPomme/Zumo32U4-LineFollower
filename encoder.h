#ifndef ENCODER_H
#define ENCODER_H
#include "Zumo32U4.h"

/**
 * @brief Klasse voor het uitlezen van de Zumo encoders.
 */
class Encoder{
public:

  /** @brief dit is de constructor */
  Encoder();

  /** @brief dit intialiseert de encoders */
  void init();

  /** @brief dit geeft aan hoeveel counts de linker encoder geeft */
  int getCountsLeft();

  /** @brief dit geeft aan hoeveel counts de rechter encoder geeft */
  int getCountsRight();

  /** @brief dit rekent de counts naar centimeter */
  float countsToCm(int counts);

  void resetEncoders();


private:
  /** @brief ZUMO encoder object voor het uitlezen van beide wielen */
  Zumo32U4Encoders extraEncoder;

  /** @brief aantal encoder count per gear ratio. rekensom is 75.81 x 12 ≈ 909.7 CPR agerond 910 */
  const int count = 910;

  /** @brief wheel diameter in cm */
  const float wheel;

  /** @brief afstand per cm per count de berkeneing is (pi x wheel) / count */
  const float cm;

  /** @brief opgeslagen count waarde van de linker encoder */
  long countLeft;

  /** @brief opgeslagen count waarde van de rechter encoder */
  long countRight;

  /** @brief geeft aan of init() is uitgevoerd */
  bool initialized;

};
#endif