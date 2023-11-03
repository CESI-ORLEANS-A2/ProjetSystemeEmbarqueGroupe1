#include "Arduino.h"

extern int counter2;
extern unsigned long remains2;
extern void (*callback2)();

void stopTimer2();
void createTimer2 (long delay, void (*handler)());
void initTimer2();