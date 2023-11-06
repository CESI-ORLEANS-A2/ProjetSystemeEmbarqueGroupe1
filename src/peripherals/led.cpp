#include "peripherals/led.hpp"

ChainableLED led(LED_CLK_PIN, LED_DATA_PIN, NUMBER_OF_LEDS);
int LEDCounter = 0;

int LEDFactor = 0;
unsigned long LEDfrequency = 0;
void (*color1)();
void (*color2)();
void (*LEDcallback)();

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
void switchLEDToPurple() {
    led.setColorRGB(LED_ID, 255, 0, 255);
}
void switchLEDToRedBlue() {
    initLEDLoop(&switchLEDToBlue, 1);
    // initLEDTimer(&switchLEDToRed, &switchLEDToBlue, 1, 10, LED_BLINK_FREQUENCY);
}
void switchLEDToRedYellow() {
    initLEDLoop(&switchLEDToYellow, 1);
    // initLEDTimer(&switchLEDToRed, &switchLEDToYellow, 1, 10, LED_BLINK_FREQUENCY);
}
void switchLEDToRedGreen() {
    // initLEDLoop(&switchLEDToGreen, 1);
    initLEDTimer(&switchLEDToRed, &switchLEDToGreen, 1, 10, LED_BLINK_FREQUENCY);
}
void switchLEDToRed2Green() {
    initLEDTimer(&switchLEDToRed, &switchLEDToGreen, 2, 10, LED_BLINK_FREQUENCY);
}
void switchLEDToRedWhite() {
    initLEDLoop(&switchLEDToWhite, 1);
}
void switchLEDToRed2White() {
    initLEDLoop(&switchLEDToWhite, 2);
}
void initLEDLoop(void (*switchLED)(), const int factor) {
    // On initialise le compteur de cycle d'activation de la LED
    LEDCounter = factor;
    while (true) {
        // Si le compteur est à 0, on le réinitialise et on change la couleur de la LED
        if (LEDCounter == 0) {
            LEDCounter = factor;
            switchLED();
        }
        // Sinon on décrémente le compteur 
        else {
            // Si le compteur est à 1, on passe la LED en rouge
            if (LEDCounter == factor)
                switchLEDToRed();
            LEDCounter--;
        }
        // On attend 1 seconde
        delay(1000);
    }
}

void LEDInterrupt() {
    if (LEDCounter != 0) {
        LEDCounter--;
        createTimer2(LEDfrequency, &LEDInterrupt);
    }
    else LEDcallback();

    if (LEDCounter % LEDFactor == 0)
        color1();
    else if (LEDCounter % LEDFactor == LEDFactor - 1)
        color2();
}

void initLEDTimer(void (*switchLED1)(), void (*switchLED2)(), int factor, unsigned long duration, unsigned long frequency) {
    LEDCounter = duration; // TODO commenter
    color1 = switchLED1;
    color2 = switchLED2;
    LEDcallback = mode == MAINTENANCE_MODE ? &switchLEDToOrange :
        mode == STANDARD_MODE ? &switchLEDToGreen :
        mode == ECONOMY_MODE ? &switchLEDToBlue :
        &switchLEDToYellow;
    LEDFactor = factor > 0 ? +1 : 2;
    LEDfrequency = frequency;

    if (LEDCounter % LEDFactor == 0)
        color1();
    else
        color2();

    createTimer2(LEDfrequency, &LEDInterrupt);
}

void stopLEDTimer() {
    stopTimer2();
    LEDcallback();
}