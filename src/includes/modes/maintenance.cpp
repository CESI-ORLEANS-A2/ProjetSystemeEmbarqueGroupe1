#include "includes/modes/maintenance.hpp"

void switchToMaintenanceMode() {
    previousMode = mode;
    mode = MAINTENANCE_MODE;
    switchLEDToYellow();
}
void runMaintenanceModeStep() {
    if (liveMode) {
        if (Serial.available()) {
            int data = Serial.read();
            if (data == '\n') {
                stopLiveMode();
#if INTERPRETER
                Serial.print(F("\n\r> "));
#endif
                return;
            }
        }
    }

    acquisition();
};
void printSwitchToMaintenance() {
    Serial.println(F("Passage en mode maintenance"));
}
void printLiveMode() {
    Serial.println(F("Mode live activé"));
}