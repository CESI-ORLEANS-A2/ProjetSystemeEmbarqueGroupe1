#include "includes/acquisition.hpp"

long previousAcquisition = NULL;

void acquisition() {

    if (previousAcquisition && millis() - previousAcquisition < (mode == MAINTENANCE_MODE ? ACQUISITION_DELAY_MANTENANCE : ACQUISITION_DELAY)) return;

    previousAcquisition = millis();

#if LIVE_MODE_SERIAL_OUTPUT == OUTPUT_JSON
    if (liveMode) Serial.print(F("{"));
#endif

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        if (!sensors[i]->enabled) continue;
        if (mode == ECONOMY_MODE && !sensors[i]->economy) continue;

        const long measure = sensors[i]->measure();

        if (liveMode) {
            char name[20];
            strcpy_P(name, sensors[i]->name);

#if LIVE_MODE_SERIAL_OUTPUT == OUTPUT_JSON
            Serial.print(F("\""));
            Serial.print(name);
            Serial.print(F("\":"));
            Serial.print(measure);
            if (i < NUMBER_OF_SENSORS - 1) Serial.print(F(","));
#elif LIVE_MODE_SERIAL_OUTPUT == OUTPUT_CSV
            Serial.print(measure);
            if (i < NUMBER_OF_SENSORS - 1) Serial.print(F(";"));
#endif
        }
    }
    if (liveMode)
#if LIVE_MODE_SERIAL_OUTPUT == OUTPUT_JSON
        Serial.println(F("}"));
#else
        Serial.println();
#endif
}