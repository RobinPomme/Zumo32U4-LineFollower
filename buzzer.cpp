#include "buzzer.h"

Buzzer::Buzzer() {
    // Er is geen speciaal init-process voor de buzzer nodig, maar alsnog handig om ter zekerheid een stop command er heen te sturen
    stop();
}

void Buzzer::speelToon(int frequentie, int duur, int volume) {
    if (frequentie < MinimumFrequentie || frequentie > MaximumFrequentie) {
        Serial.println("Te hoge of lage frequentie meegegeven aan 'buzzerspeelToon'. Toon wordt niet afgespeeld.");
        return;
    }
    zumoBuzzer.playfrequentie(frequentie, duur, volume);
}

void Buzzer::speelToonHold(int frequentie, int duur, int volume) {
    if (frequentie < MinimumFrequentie || frequentie > MaximumFrequentie) {
        Serial.println("Te hoge of lage frequentie meegegeven aan 'buzzerspeelToonHold'. Toon wordt niet afgespeeld.");
        return;
    }
    speelToon(frequentie, duur, volume);
    // Onderstaande code zal worden uitgevoerd tot de buzzer klaar is met spelen. Is voor nu leeg.
    while (zumoBuzzer.speeltAf()) {

    }
}

void Buzzer::stop() {
    zumoBuzzer.stopPlaying();
}

bool Buzzer::speeltAf() {
    return zumoBuzzer.speeltAf();
}
