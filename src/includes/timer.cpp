#include "includes/timer.hpp"

int counter = 0;
void (*callback)() = NULL;
unsigned long remains = 0;

ISR(TIMER1_COMPA_vect) {
    if (counter == 0) {
        if (remains > 0) {
            createTimer(remains, callback);
        }
        else {
            if (callback != NULL) {
                (*callback)();
                stopTimer();
            }
        }
    }
    else counter--;
}

void initTimer() {};

void createTimer(long delay, void (*handler)()) {
    noInterrupts();
    unsigned long ticks = (delay * 16) / 1024;
    if (ticks > 65535) {
        remains = ticks % 65535;
        counter = (ticks - remains) / 65535;
        ticks = 65535;
    }
    else {
        remains = 0;
        counter = 0;
    }

    callback = handler;

    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    OCR1A = ticks - 1;
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
    interrupts();
}
void stopTimer() {
    TIMSK1 &= (0 << OCIE1A);
}