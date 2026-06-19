#include "buzzer.h"

void Buzzer::init() {
    // Er is geen speciaal init-process voor de buzzer nodig, maar alsnog handig om ter zekerheid een stop command er heen te sturen
    stop();
}

void Buzzer::playTone(int frequency, int duration, int volume) {
    if (frequency < MinimumFrequency || frequency > MaximumFrequency) {
        Serial.println("Te hoge of lage frequentie meegegeven aan 'buzzerPlayTone'. Toon wordt niet afgespeeld.");
        return;
    }
    zumoBuzzer.playFrequency(frequency, duration, volume);
}

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

void Buzzer::stop() {
    zumoBuzzer.stopPlaying();
}

bool Buzzer::isPlaying() {
    return zumoBuzzer.isPlaying();
}
