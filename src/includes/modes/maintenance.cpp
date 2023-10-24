#include "includes/modes/maintenance.hpp"

void switchToMaintenanceMode() {
    previousMode = mode;
    mode = MAINTENANCE_MODE;
    switchLEDToYellow();

    // TODO Démonter la carte SD
}
void quitMaintenanceMode() {
    // TODO Remonter la carte SD
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
    }
#endif

    acquisition(&printData);
};
void printSwitchToMaintenance() {
    Serial.println(F("Passage en mode maintenance"));
}
void printLiveMode() {
    Serial.println(F("Mode live activé"));
}