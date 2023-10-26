#ifndef Clock_h
#define Clock_h

#include <DS1307.h>

extern DS1307 clock;

void initClock();
int readClock();

#endif