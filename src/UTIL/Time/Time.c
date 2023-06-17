/*************************************************************
 * 
 * Filename: Time.c
 * Description: Implementation of a time library.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "Time.h"

uint64_t Time_toMS(Time_t t)
{ 
    uint64_t ms = 0;

    ms += t.ms;
    ms += t.seconds * MS_PER_SECOND;
    ms += t.minutes * MS_PER_MINUTE;
    ms += t.hours * MS_PER_HOUR;

    return ms;
}

Time_t Time_fromMS(uint64_t ms) {
    Time_t t;

    t.hours = ms / MS_PER_HOUR;
    ms -= t.hours * MS_PER_HOUR;

    t.minutes = ms / MS_PER_MINUTE;
    ms -= t.minutes * MS_PER_MINUTE;

    t.seconds = ms / MS_PER_SECOND;
    ms -= t.seconds * MS_PER_SECOND;

    t.ms = ms;

    return t;
}

Time_t Time_add(Time_t t1, Time_t t2) {
    return Time_fromMS(Time_toMS(t1) + Time_toMS(t2));
}

Time_t Time_subtract(Time_t t1, Time_t t2) {
    return Time_fromMS(Time_toMS(t1) - Time_toMS(t2));
}