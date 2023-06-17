/*************************************************************
 * 
 * Filename: Time.h
 * Description: Header file of a time library.
 * Author: Eng. Hazem Anwer
 * Github: https://github.com/hazemanwer2000
 * 
 *************************************************************/

#include "Std_Types.h"

#define SECONDS_PER_MINUTE              60
#define MINUTES_PER_HOUR                60
#define SECONDS_PER_HOUR                (SECONDS_PER_MINUTE * MINUTES_PER_HOUR)

typedef struct {
    uint32_t hours;
    uint16_t ms;
    uint8_t seconds;
    uint8_t minutes;
} Time_t;

Time_t Time_add(Time_t t1, Time_t t2);

Time_t Time_subtract(Time_t t1, Time_t t2);

uint64_t Time_toSeconds(Time_t t);

Time_t Time_fromSeconds(uint64_t seconds);