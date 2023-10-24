#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

extern int counter;
extern void (*callback)();
extern unsigned long remains;

void initTimer();
void createTimer(long delay, void (*handler)());
void stopTimer();

#endif