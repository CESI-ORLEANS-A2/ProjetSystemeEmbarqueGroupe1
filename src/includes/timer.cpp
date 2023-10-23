#include "includes/timer.hpp"

// int counter = 0;
// void (*callback)() = NULL;
// int remainder = 0;

// ISR(TIMER1_COMPA_vect) {
//     if (counter == 0) {
//         if (remainder > 0) {
//             createTimer(remainder, callback);
//         }
//         else (*callback)();
//     }
//     else counter--;
// }

// void attachButtonInterrupt(int pin, int delay, void (*handler)()) {
//     auto boundHandler = [pin, delay, handler]() {
//         Serial.println(F("Button pressed"));
//         if (digitalRead(pin) == HIGH) {
//             if (TCCR1B != _BV(WGM13)) stopTimer();
//         }
//         else createTimer(delay, handler);
//         };
//     attachInterrupt(digitalPinToInterrupt(pin), (void (*)()) (&boundHandler), CHANGE);
// }

// void initTimer() {};

// void createTimer(int delay, void (*handler)()) {
//     int ticks = (delay * 16000) / 1024;
//     if (ticks > 65535) {
//         remainder = ticks % 65535;
//         counter = (ticks - remainder) / 65535;
//         ticks = 65535;
//     }
//     else {
//         remainder = 0;
//         counter = 0;
//     }

//     callback = handler;

//     noInterrupts();
//     TCCR1A = 0;
//     TCCR1B = 0;
//     TCNT1 = 0;
//     OCR1A = ticks - 1;
//     TCCR1B |= (1 << CS12) | (1 << CS10);
//     TIMSK1 |= (1 << OCIE1A);
//     interrupts();
// }
// void stopTimer() {
//     TIMSK1 &= (0 << OCIE1A);
// };