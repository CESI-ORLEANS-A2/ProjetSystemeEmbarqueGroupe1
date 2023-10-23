#include <Arduino.h>

#include "TimerOne.h"

// Macro permettant d'attacher une interruption sur un bouton et de déclencher un timer pour vérifier le délai d'appui
#define attachButtonInterrupt(pin, delay, callback) {           \
    attachInterrupt(digitalPinToInterrupt(pin), []() {          \
        if (digitalRead(pin) == HIGH) {                         \
            if (TCCR1B != _BV(WGM13)) Timer1.stop();            \
        } else                                                  \
            Timer1.attachInterrupt(&callback, delay);           \
    }, CHANGE);                                                 \
} 

// Macro permettant d'initialiser le timer
#define initTimer(delay) {                                      \
    Timer1.initialize(delay);                                   \
}

// extern int counter;
// extern void (*callback)();
// extern int remainder;

// void attachButtonInterrupt(int pin, int delay, void (*callback)());

// void initTimer();
// void createTimer(int delay, void (*handler)());
// void stopTimer();