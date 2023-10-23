#include "consts.hpp"

#include <Adafruit_BME280.h>

extern Adafruit_BME280 bme;
extern bool isInit;


void initBME();
float readTemperature();
float readHumidity();
float readPressure();
