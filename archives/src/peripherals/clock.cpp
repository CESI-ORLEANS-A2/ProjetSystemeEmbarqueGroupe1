#include "peripherals/clock.hpp"

DS1307 clock;

int lastHour;
int lastMinute;
int lastSecond;
int lastDay;
int lastMonth;
int lastYear;
int lastDayOfWeek;

void initClock() {
    clock.begin();
}
bool readClock() {
    return true;
    // TODO Lecture de l'horloge
}