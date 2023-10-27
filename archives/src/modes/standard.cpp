#include "modes/standard.hpp"

void switchToStandardMode() {
    previousMode = mode;
    mode = STANDARD_MODE;
    switchLEDToGreen();
};
void quitStandardMode() {

}
void runStandardModeStep() {
    acquisition(&saveData);
};

void printSwitchToStandard() {
    Serial.println(F("Passage en mode standard"));
}