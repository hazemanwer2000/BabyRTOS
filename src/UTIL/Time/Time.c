/*************************************************************
 * 
 * Filename: Time.c
 * Description: Implementation of a time library.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "Time.h"

uint64_t Time_toSeconds(Time_t t)
{ 
    uint64_t seconds = 0;

    seconds += t.seconds;
    seconds += t.minutes * SECONDS_PER_MINUTE;
    seconds += t.hours * SECONDS_PER_HOUR;
}

Time_t Time_fromSeconds(uint64_t seconds) {
    Time_t t;

    t.ms = 0;

    t.hours = seconds / SECONDS_PER_HOUR;
    seconds -= t.hours * SECONDS_PER_HOUR;

    t.minutes = seconds / SECONDS_PER_MINUTE;
    seconds -= t.minutes * SECONDS_PER_MINUTE;

    t.seconds = seconds;

    return t;
}

Time_t Time_add(Time_t t1, Time_t t2) {
    return Time_fromSeconds(Time_toSeconds(t1) + Time_toSeconds(t2));
}

Time_t Time_subtract(Time_t t1, Time_t t2) {
    return Time_fromSeconds(Time_toSeconds(t1) - Time_toSeconds(t2));
}