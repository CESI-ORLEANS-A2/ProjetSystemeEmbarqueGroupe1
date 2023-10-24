#include "main.hpp"
#include "includes/acquisition.hpp"
#include "includes/peripherals/serial.hpp"

void switchToMaintenanceMode();
void quitMaintenanceMode();
void runMaintenanceModeStep();

void printSwitchToMaintenance();
void printLiveMode();