#ifndef Acquisition_h
#define Acquisition_h

#include "main.hpp"

extern unsigned long previousAcquisition;
extern int numberOfErrors;
extern bool errors[NUMBER_OF_SENSORS];
extern bool underAcquisition;
extern int numberOfErrors;

void acquisition(void (*callback)());

#endif