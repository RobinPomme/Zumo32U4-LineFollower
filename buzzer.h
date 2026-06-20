#ifndef BUZZER_H
#define BUZZER_H

#include <Wire.h>
#include <Zumo32U4.h>

/**
 * @brief Klasse voor het beheer van de buzzer op de Zumo32U4.
 *
 * Deze klasse geeft functionaliteit om tonen af te spelen, te stoppen en te controleren of er een toon wordt afgespeeld.
 */
class Buzzer {
public:
    /** @brief Construeert een nieuw buzzer object. */
    Buzzer();

    /**
     * @brief Speelt een toon af met de gegeven frequentie, lengte en volume.
     * @param frequency De frequentie van de toon in Hz. (Tussen 10Hz en 10kHz)
     * @param duration De lengte van de toon in milliseconden.
     * @param volume Het volume van de toon (Van 0 t/m 15).
     */
    void playTone(int frequency, int duration, int volume = DefaultVolume);

    /**
     * @brief Speelt een toon af en wacht tot deze klaar is.
     * @param frequency De frequentie van de toon in Hz. (Tussen 10Hz en 10kHz)
     * @param duration De lengte van de toon in milliseconden.
     * @param volume Het volume van de toon (Van 0 t/m 15).
     */
    void playToneHold(int frequency, int duration, int volume = DefaultVolume);

    /** @brief Stopt het afspelen van de huidige toon. */
    void stop();

    /**
     * @brief Controleert of de buzzer momenteel een toon afspeelt.
     * @return true als er een toon wordt afgespeeld, anders false.
     */
    bool isPlaying();

private:
    Zumo32U4Buzzer zumoBuzzer;
    static const int DefaultVolume = 10; // 0 - 15
    static const int MinimumFrequency = 10; // in ms
    static const int MaximumFrequency = 10000; // 10Hz - 10kHz
};

#endif // BUZZER_H
