#include "main.hpp"
#include "acquisition.hpp"
#include "peripherals/sd.hpp"
#include "peripherals/serial.hpp"

void switchToMaintenanceMode();
void quitMaintenanceMode();
void runMaintenanceModeStep();

void printLiveMode();