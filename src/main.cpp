#include <Arduino.h>
#include <Hoymiles.h>

uint64_t inv_serial = 0x114181014156UL;
uint64_t dtu_serial = 0x99978563412UL;

void setupHoymiles() {
    Hoymiles.init();
    Hoymiles.getRadio()->setPALevel(RF24_PA_MAX);
    Hoymiles.getRadio()->setDtuSerial(dtu_serial);
    Hoymiles.setPollInterval(5);
}

void setupInverter() {
    auto inv   = Hoymiles.addInverter("Gartenhaus", inv_serial);
    auto stats = inv->Statistics();

    uint8_t channel_count = stats->getChannelCount();
    Serial.printf("Channel Count: %d\r\n", channel_count);
}

void printStats() {
    static unsigned long last_millis;
    unsigned long        current_millis = millis();
    if (current_millis - last_millis < 5000) return;
    last_millis = current_millis;

    uint8_t num_inverters = Hoymiles.getNumInverters();

    for (size_t inv_num = 0; inv_num < num_inverters; inv_num++) {
    
        auto    inv           = Hoymiles.getInverterByPos(inv_num);
        auto    stats         = inv->Statistics();
        uint8_t channel_count = stats->getChannelCount();

        for (uint8_t channel = 0; channel < channel_count + 1; channel++) {
            Serial.printf("Channel %d\r\n", channel);
            for (uint8_t field = 0; field < 20; field++) {
                if (stats->hasChannelFieldValue(channel, field)) {
                    float       value = stats->getChannelFieldValue(channel, field);
                    const char* name  = stats->getChannelFieldName(channel, field);
                    const char* unit  = stats->getChannelFieldUnit(channel, field);
                    Serial.printf("%s = %0.2f %s\r\n", name, value, unit);
                }
            }
    
            Serial.println();
        }
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    setupHoymiles();
    setupInverter();
}

void loop() {
    Hoymiles.loop();
    printStats();
}