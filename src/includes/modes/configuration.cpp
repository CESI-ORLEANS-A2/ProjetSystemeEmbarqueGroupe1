#include "includes/modes/configuration.hpp"

void switchToConfigurationMode() {
    previousMode = mode;
    mode = CONFIGURATION_MODE;
};
void runConfigurationModeStep() {};

void printSwitchToConfiguration() {
    Serial.println(F("Passage en mode configuration"));
}