#include "includes/peripherals/led.hpp"

ChainableLED led(LED_CLK_PIN, LED_DATA_PIN, NUMBER_OF_LEDS);

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