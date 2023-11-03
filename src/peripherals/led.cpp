#include "peripherals/led.hpp"
#include "timer2.hpp"

ChainableLED led(LED_CLK_PIN, LED_DATA_PIN, NUMBER_OF_LEDS);
int ledCounter;
int fact;
int sequenceCounter = 10;
void (*color)();

void initLED() {
    led.init();
}
void switchLEDToRed() {
    led.setColorRGB(LED_ID, 255, 0, 0);
}
void switchLEDToGreen() {
    led.setColorRGB(LED_ID, 0, 255, 0);
}
void switchLEDToBlue() {
    led.setColorRGB(LED_ID, 0, 0, 255);
}
void switchLEDToYellow() {
    led.setColorRGB(LED_ID, 255, 255, 0);
}
void switchLEDToOrange() {
    led.setColorRGB(LED_ID, 248, 170, 49);
}
void switchLEDToWhite() {
    led.setColorRGB(LED_ID, 255, 255, 255);
}
void switchLEDToRedBlue() {
    initLEDLoop(&switchLEDToBlue, 1);
}
void switchLEDToRedYellow() {
    initLEDLoop(&switchLEDToYellow, 1);
}
void switchLEDToRedGreen() {
    initLEDLoop(&switchLEDToGreen, 1);
}
void switchLEDToRed2Green() {
    initLEDLoop(&switchLEDToGreen, 2);
}
void switchLEDToRedWhite() {
    initLEDLoop(&switchLEDToWhite, 1);
}
void switchLEDToRed2White() {
    initLEDLoop(&switchLEDToWhite, 2);
}
void initLEDLoop(void (*switchLED)(), const int factor) {
    ledCounter = factor;
    while (true) {
        if (ledCounter == 0) {
            ledCounter = factor;
            switchLED();
        }
        else {
            if (ledCounter == factor)
                switchLEDToRed();
            ledCounter--;
        }
        delay(1000);
    }
}

void LEDLoopTimer(void (*switchLED)(), const int factor) {
    color = switchLED;
    fact = factor;
    if (sequenceCounter != 0) {
        if (!(sequenceCounter % 2)) {
            createTimer2(1e6 * factor, switchLED);
        }
        else {
            if (sequenceCounter % 2){
                createTimer2(1e6, switchLEDToRed);
            }
        }
    }
    else {
        sequenceCounter = 10;
    }
}