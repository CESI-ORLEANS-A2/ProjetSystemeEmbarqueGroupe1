#ifndef Clock_h
#define Clock_h

#include <DS1307.h>

extern DS1307 clock;

#define initClock() clock.begin()
#define readClock() clock.getTime()

#define getHour() clock.hour
#define getMinute() clock.minute
#define getSecond() clock.second
#define getDay() clock.dayOfMonth
#define getMonth() clock.month
#define getYear() clock.year
#define getYearFull() clock.year + 2000
#define getDayOfWeek() clock.dayOfWeek

void setHour(int hour);
void setMinute(int minute);
void setSecond(int second);
void setDay(int day);
void setMonth(int month);
void setYear(int year);
void setYearFull(int year);
void setDayOfWeek(int dayOfWeek);

#endif