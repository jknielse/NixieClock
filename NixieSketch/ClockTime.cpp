#include "Arduino.h"
#include "ClockTime.h"

int daysAtMonth[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

bool isLeapYear(long year){
    if (year % 400 == 0){
        return true;
    }
    if (year % 100 == 0){
        return false;
    }
    if (year % 4 == 0){
        return true;
    }
    return false;
}

Timestamp::Timestamp(unsigned long year, unsigned long month, unsigned long day, unsigned long hours, unsigned long mins, unsigned long secs, unsigned long centisecs){
    msecs = (((hours * 60UL + mins) * 60UL + secs) * 100UL + centisecs) * 10UL;
    unsigned long yeardays = 0;
    long yearCount = year - 2000L;
    for (long y = 0; y < yearCount; y++){
        if (isLeapYear(y)){
            yeardays += 366;
        } else {
            yeardays += 365;
        }
    }

    long monthdays = daysAtMonth[month];
    if (isLeapYear(year) && month > 2){
        monthdays++;
    }

    days = day + monthdays + yeardays;
}

unsigned long Timestamp::getDays(){
    return days;
}

unsigned long Timestamp::getMilliseconds(){
    return msecs;
}

long operator-(Timestamp t1, Timestamp t2)
{
     return (long)(t1.getDays() - t2.getDays()) * 86400000L + (t1.getMilliseconds() - t2.getMilliseconds());
}


ClockTime::ClockTime()
{
    offset_secs = 0;
    latest_arduino_time = 0;
    saved_arduino_time_1 = 0;
    saved_arduino_time_2 = 0;
}

void ClockTime::setTime(Timestamp real_time, unsigned long arduino_time) {
    latest_arduino_time = arduino_time;
    latest_real_time = real_time;

    // i.e. if this is the first time setTime has been called
    if (saved_arduino_time_2 == 0){
        saved_arduino_time_1 = latest_arduino_time;
        saved_arduino_time_2 = latest_arduino_time;
        saved_real_time_1 = latest_real_time;
        saved_real_time_2 = latest_real_time;
    } else {
        // If the newer of the two saved times is older than a day
        if ((long)(latest_real_time - saved_real_time_1) > 86400000L){
            saved_real_time_2 = saved_real_time_1;
            saved_arduino_time_2 = saved_arduino_time_1;
            saved_real_time_1 = latest_real_time;
            saved_arduino_time_1 = latest_arduino_time;
        }
    }
}

void ClockTime::setOffset(long secs){
    offset_secs = secs;
}

double ClockTime::clockAdjustFactor(){
    long real_elapsed_time = latest_real_time - saved_real_time_2;
    long arduino_elapsed_time = latest_arduino_time - saved_arduino_time_2;
    // If more than half a minute has elapsed, we might have a chance of getting a reasonable measurement here.
    if (real_elapsed_time > 30000L){
        return (double)real_elapsed_time / (double)arduino_elapsed_time;
    }
    return 1.0;
}

// seconds since start of day
long ClockTime::getSecs(){
    long current_time = latest_real_time.getMilliseconds() + (unsigned long)((millis() - latest_arduino_time) * clockAdjustFactor()) + offset_secs * 1000L;
    return current_time/1000UL;
}

