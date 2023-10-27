#include "consts.hpp"
#include <ChainableLED.h>

extern ChainableLED led;
extern int ledCounter;

void initLED();
void switchLEDToRed();
void switchLEDToGreen();
void switchLEDToBlue();
void switchLEDToYellow();
void switchLEDToRedBlue();
void switchLEDToRedYellow();
void switchLEDToRedGreen();
void switchLEDToRed2Green();
void switchLEDToRedWhite();
void switchLEDToRed2White();

void initLEDLoop(void (*switchLED)(), const int factor);