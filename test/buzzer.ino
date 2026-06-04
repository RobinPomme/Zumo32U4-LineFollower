#include "buzzer.h"

Buzzer Buzzer;

/** \brief Initialiseert de buzzer. */
void buzzerInit() {
    Buzzer.init();
}

/** \brief Speel toon. Controleert of frequentie binnen range valt. */
void buzzerPlayTone(int frequency, int duration, int volume = 10) {
    Buzzer.playTone(frequency, duration, volume);
}

/** \brief Speel toon en wacht met een while blok tot buzzer klaar is met spelen. Controleert of frequentie binnen range valt. */
void buzzerPlayToneHold(int frequency, int duration, int volume = 10) {
    Buzzer.playToneHold(frequency, duration, volume);
}

/** \brief Stop de buzzer */
void stopBuzzer() {
    Buzzer.stop();
}

/** \brief Tool om te controleren of de buzzer een toon speelt */
bool buzzerIsPlaying() {
    return Buzzer.isPlaying();
}

// // Demo!
// void setup() {
//     buzzerInit();
// }

// void loop() {
//     buzzerPlayTone(440, 300); // speel 440 Hz voor 300 ms
//     delay(500);
//     stopBuzzer();
//     delay(1000);
// }
