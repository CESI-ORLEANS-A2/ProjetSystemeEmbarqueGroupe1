#ifndef Serial_h
#define Serial_h

#include <Arduino.h>
#include "consts.hpp"

extern bool isSerialInit;

void initSerial();
void print(String message);

#endif