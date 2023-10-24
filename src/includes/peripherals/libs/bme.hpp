#include "consts.hpp"
#include "includes/modes/error.hpp"

#include <Seeed_BME280.h>

extern BME280 bme;
extern bool isInit;


void initBME();
float readTemperature();
float readHumidity();
float readPressure();
