#include "peripherals/clock.hpp"

DS1307 clock;

void initClock() {
    clock.begin();
}
bool readClock() {
    clock.getTime();
    return true;
}
int getHour() {
    return clock.hour;
}
int getMinute() {
    return clock.minute;
}
int getSecond() {
    return clock.second;
}
int getDay() {
    return clock.dayOfMonth;
}
int getMonth() {
    return clock.month;
}
int getYear() {
    return clock.year;
}
int getYearFull() {
    return clock.year + 2000;
}
int getDayOfWeek() {
    return clock.dayOfWeek;
}
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