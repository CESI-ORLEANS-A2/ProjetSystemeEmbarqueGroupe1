#include "modes/economy.hpp"

void switchToEconomyMode() {
    previousMode = mode;
    mode = ECONOMY_MODE;
};
void quitEconomyMode() {
    
}
void runEconomyModeStep() {
    acquisition(&saveData);
};
