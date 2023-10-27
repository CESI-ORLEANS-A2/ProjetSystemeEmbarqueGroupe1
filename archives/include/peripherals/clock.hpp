#ifndef Clock_h
#define Clock_h

#include <DS1307.h>

extern DS1307 clock;

extern int lastHour;
extern int lastMinute;
extern int lastSecond;
extern int lastDay;
extern int lastMonth;
extern int lastYear;
extern int lastDayOfWeek;

void initClock();
bool readClock();

#endif