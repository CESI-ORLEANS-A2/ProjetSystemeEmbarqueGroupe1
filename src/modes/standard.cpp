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
