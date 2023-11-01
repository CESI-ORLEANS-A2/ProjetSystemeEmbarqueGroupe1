#include "libs/bme.hpp"

BME280 bme;
bool isInit = false;

void initBME() {
    if (isInit) return;
    isInit = true;

    if (!bme.init())
        switchToErrorMode(ERROR_SENSOR_ACCESS);
}
