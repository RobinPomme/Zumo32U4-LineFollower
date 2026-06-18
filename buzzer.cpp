#include "buzzer.h"

/** \brief Initialiseert de buzzer. */
void Buzzer::init() {
    // Er is geen speciaal init-process voor de buzzer nodig, maar alsnog handig om ter zekerheid een stop command er heen te sturen
    stop();
}

/** \brief Speelt een toon af met de gegeven frequentie, lengte en volume. */
void Buzzer::playTone(int frequency, int duration, int volume) {
    if (frequency < MinimumFrequency || frequency > MaximumFrequency) {
        Serial.println("Te hoge of lage frequentie meegegeven aan 'buzzerPlayTone'. Toon wordt niet afgespeeld.");
        return;
    }
    zumoBuzzer.playFrequency(frequency, duration, volume);
}

/** \brief Speelt een toon af en wacht tot deze klaar is. */
void Buzzer::playToneHold(int frequency, int duration, int volume) {
    if (frequency < MinimumFrequency || frequency > MaximumFrequency) {
        Serial.println("Te hoge of lage frequentie meegegeven aan 'buzzerPlayToneHold'. Toon wordt niet afgespeeld.");
        return;
    }
    playTone(frequency, duration, volume);
    // Onderstaande code zal worden uitgevoerd tot de buzzer klaar is met spelen. Is voor nu leeg.
    while (zumoBuzzer.isPlaying()) {

    }
}

/** \brief Stopt het afspelen van de buzzer. */
void Buzzer::stop() {
    zumoBuzzer.stopPlaying();
}

/** \brief Controleert of de buzzer momenteel een toon afspeelt. */
bool Buzzer::isPlaying() {
    return zumoBuzzer.isPlaying();
}
