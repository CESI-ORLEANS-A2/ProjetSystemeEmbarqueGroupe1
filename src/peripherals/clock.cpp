#include "peripherals/clock.hpp"

DS1307 clock;

void setHour(int hour) {
    clock.hour = hour;
    clock.setTime();
}
void setMinute(int minute) {
    clock.minute = minute;
    clock.setTime();
}
void setSecond(int second) {
    clock.second = second;
    clock.setTime();
}
void setDay(int day) {
    clock.dayOfMonth = day;
    clock.setTime();
}
void setMonth(int month) {
    clock.month = month;
    clock.setTime();
}
void setYear(int year) {
    clock.year = year - 2000;
    clock.setTime();
}
void setYearFull(int year) {
    clock.year = year - 2000;
    clock.setTime();
}
void setDayOfWeek(int dayOfWeek) {
    clock.dayOfWeek = dayOfWeek;
    clock.setTime();
}