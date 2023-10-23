#include "includes/modes/standard.hpp"

void switchToStandardMode() {
    previousMode = mode;
    mode = STANDARD_MODE;
    switchLEDToGreen();
};
void runStandardModeStep() {};

void printSwitchToStandard() {
    Serial.println(F("Passage en mode standard"));
}