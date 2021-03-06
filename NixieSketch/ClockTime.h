#ifndef ClockTime_h
#define ClockTime_h

#include "Arduino.h"
#include <limits.h>

class Timestamp
{
    public:
        Timestamp(unsigned long year, unsigned long month, unsigned long day, unsigned long hours, unsigned long mins, unsigned long secs, unsigned long centisecs);
        unsigned long getSeconds();
        long getMilliseconds();
        friend long operator-(Timestamp t1, Timestamp t2);
    private:
        unsigned long epoch_secs;
        long msecs;
};

class TimeZone
{
    public:
        TimeZone(long i_offset, unsigned long i_next_time, long i_next_offset);
        // Only garunteed to work if increasing times are requested.
        unsigned long getSeconds(unsigned long unix_timestamp);
    private:
        long offset;
        unsigned long next_time;
        long next_offset;
};

class ClockTime
{
    public:
        ClockTime();
        void setTime(Timestamp real_time, unsigned long arduino_time);
        void setTimeZone(TimeZone timezone);
        unsigned long localTime();
        unsigned long unixTime();
        unsigned long getNextInterrupt();
    private:
        unsigned long getMilliseconds();
        double clockAdjustFactor();
        TimeZone timezone = TimeZone(0, LONG_MAX, 0);
        unsigned long latest_arduino_time;
        Timestamp latest_real_time = Timestamp(2000UL, 10UL, 1UL, 0UL, 0UL, 0UL, 0UL);
        unsigned long saved_arduino_time_1;
        Timestamp saved_real_time_1 = Timestamp(2000UL, 10UL, 1UL, 0UL, 0UL, 0UL, 0UL);
        unsigned long saved_arduino_time_2;
        Timestamp saved_real_time_2 = Timestamp(2000UL, 10UL, 1UL, 0UL, 0UL, 0UL, 0UL);
};

#endif
