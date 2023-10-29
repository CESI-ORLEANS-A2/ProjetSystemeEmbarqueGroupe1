#include "modes/maintenance.hpp"

void switchToMaintenanceMode() {
    previousMode = mode;
    mode = MAINTENANCE_MODE;
    switchLEDToYellow();

    unmount();
}
void quitMaintenanceMode() {
    mount();
}
void runMaintenanceModeStep() {
#if INTERPRETER
    if (liveMode) {
        if (Serial.available()) {
            int data = Serial.read();
            if (data == '\n') {
                stopLiveMode();
                Serial.print(F("\n\r> "));
                return;
            }
        }
        acquisition(&printData);
    }
    else acquisition(NULL);
#else
    acquisition(&printData);
#endif
};
void printSwitchToMaintenance() {
    Serial.println(F("Passage en mode maintenance"));
}
void printLiveMode() {
    Serial.println(F("Mode live activé"));

#if LIVE_MODE_SERIAL_OUTPUT==OUTPUT_CSV
    printCSVHeader();
#endif
}