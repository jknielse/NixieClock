#include "Arduino.h"
#include "ClockTime.h"
#include "Time.h"
#include <limits.h>


Timestamp::Timestamp(unsigned long year, unsigned long month, unsigned long day, unsigned long hours, unsigned long mins, unsigned long secs, unsigned long centisecs){
    setTime(hours, mins, secs, day, month, year);
    epoch_secs = now();
    msecs = centisecs * 10UL;
}

unsigned long Timestamp::getSeconds(){
    return epoch_secs;
}

long Timestamp::getMilliseconds(){
    return msecs;
}

long operator-(Timestamp t1, Timestamp t2)
{
     return (long)(t1.getSeconds() - t2.getSeconds()) * 1000L + (t1.getMilliseconds() - t2.getMilliseconds());
}

TimeZone::TimeZone (long i_offset, unsigned long i_next_time, long i_next_offset) {
    offset = i_offset;
    next_time = i_next_time;
    next_offset = i_next_offset;
}

unsigned long TimeZone::getSeconds(long unix_timestamp)
{
    if (unix_timestamp > next_time) {
        offset = next_offset;
    }
    long t = unix_timestamp + offset;
    unsigned long hours = hour(t);
    unsigned long minutes = minute(t);
    unsigned long seconds = second(t);
    return (hours * 60UL + minutes) * 60UL + seconds;
}


ClockTime::ClockTime()
{
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
        if ((latest_real_time - saved_real_time_1) > 86400000UL){
            saved_real_time_2 = saved_real_time_1;
            saved_arduino_time_2 = saved_arduino_time_1;
            saved_real_time_1 = latest_real_time;
            saved_arduino_time_1 = latest_arduino_time;
        }
    }
}

void ClockTime::setTimeZone(TimeZone iTimezone) {
    timezone = iTimezone;
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

long ClockTime::getMilliseconds() {
    return latest_real_time.getMilliseconds() + (unsigned long)((millis() - latest_arduino_time) * clockAdjustFactor());
}

long ClockTime::unixTime() {
    return latest_real_time.getSeconds() + (long)((millis() - latest_arduino_time) * clockAdjustFactor())/1000L;
}

long ClockTime::localTime() {
    return timezone.getSeconds(unixTime());
}

// next time that the clock interrupt should fire
unsigned long ClockTime::getNextInterrupt(){
    return 100UL + (unsigned long)((1000UL - (getMilliseconds() % 1000UL)) / clockAdjustFactor());
}

