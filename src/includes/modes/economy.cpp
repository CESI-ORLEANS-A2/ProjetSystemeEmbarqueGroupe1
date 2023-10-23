#include "includes/modes/economy.hpp"

void switchToEconomyMode() {
    previousMode = mode;
    mode = ECONOMY_MODE;
};
void runEconomyModeStep() {};

void printSwitchToEconomy() {
    Serial.println(F("Passage en mode économique"));
}