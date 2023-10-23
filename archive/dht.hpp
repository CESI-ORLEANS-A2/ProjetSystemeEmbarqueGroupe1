#include "consts.hpp"

#if !CESI_ARDUINO

#include <dhtnew.h>

extern DHTNEW dht;

extern bool readThisStep;

void readDHT();
float readTemperature();
float readHumidity();
float readPressure();

#endif