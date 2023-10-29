#ifndef Clock_h
#define Clock_h

#include <DS1307.h>

extern DS1307 clock;

void initClock();
bool readClock();

int getHour();
int getMinute();
int getSecond();
int getDay();
int getMonth();
int getYear();
int getYearFull();
int getDayOfWeek();
void setHour(int hour);
void setMinute(int minute);
void setSecond(int second);
void setDay(int day);
void setMonth(int month);
void setYear(int year);
void setYearFull(int year);
void setDayOfWeek(int dayOfWeek);

#endif