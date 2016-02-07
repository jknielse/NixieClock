#include "Arduino.h"
#include "ClockTime.h"
#include "Time.h"

Timestamp::Timestamp(unsigned long year, unsigned long month, unsigned long day, unsigned long hours, unsigned long mins, unsigned long secs, unsigned long centisecs){
    setTime(hours, mins, secs, day, month, year);
    epoch_secs = now();
    msecs = centisecs * 10UL;
}

unsigned long Timestamp::getSeconds(){
    return epoch_secs;
}

unsigned long Timestamp::getMilliseconds(){
    return msecs;
}

unsigned long Timestamp::dayMilliseconds(){
    unsigned long hours = hour(epoch_secs);
    unsigned long minutes = minute(epoch_secs);
    unsigned long seconds = second(epoch_secs);
    return ((hours * 60UL + minutes) * 60UL + seconds) * 1000UL + msecs;
}

long operator-(Timestamp t1, Timestamp t2)
{
     return (long)(t1.getSeconds() - t2.getSeconds()) * 1000L + (t1.getMilliseconds() - t2.getMilliseconds());
}

TimeZone::TimeZone(long offset_secs, long* adjust_times, long length)
{
    len = length;
    adjusts = adjust_times;
    offset = offset_secs;
    index = 0;
}

unsigned long TimeZone::getSecs(long unix_timestamp)
{
    while ((index < len) && (adjusts[index] < unix_timestamp)) {
        offset = adjusts[index + 1];
        index += 2;
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
        if ((long)(latest_real_time - saved_real_time_1) > 86400000L){
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
    return latest_real_time.dayMilliseconds() + (unsigned long)((millis() - latest_arduino_time) * clockAdjustFactor());
}

// seconds since start of day (UTC time)
long ClockTime::getSecs() {
    return getMilliseconds()/1000UL;//timezone.getSecs(getMilliseconds()/1000UL);
}

// next time that the clock interrupt should fire
unsigned long ClockTime::getNextInterrupt(){
    return (millis() + (getMilliseconds() % 1000UL) / clockAdjustFactor());
}

