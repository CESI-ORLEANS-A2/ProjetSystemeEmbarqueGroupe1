#include "main.hpp"
#include "acquisition.hpp"
#include "peripherals/serial.hpp"

void switchToMaintenanceMode();
void quitMaintenanceMode();
void runMaintenanceModeStep();

void printSwitchToMaintenance();
void printLiveMode();