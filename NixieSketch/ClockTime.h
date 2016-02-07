#ifndef ClockTime_h
#define ClockTime_h

#include "Arduino.h"

class Timestamp
{
    public:
        Timestamp(unsigned long year, unsigned long month, unsigned long day, unsigned long hours, unsigned long mins, unsigned long secs, unsigned long centisecs);
        unsigned long getSeconds();
        unsigned long dayMilliseconds();
        unsigned long getMilliseconds();
        friend long operator-(Timestamp t1, Timestamp t2);
    private:
        long epoch_secs;
        unsigned long msecs;
};

class TimeZone
{
    public:
        TimeZone(long offset_secs, long* adjust_times, long length);
        // Only garunteed to work if increasing times are requested.
        unsigned long getSecs(long unix_timestamp);
    private:
        long len;
        long* adjusts;
        long offset;
        int index;
};

class ClockTime
{
    public:
        ClockTime();
        void setTime(Timestamp real_time, unsigned long arduino_time);
        void setTimeZone(TimeZone timezone);
        long getMilliseconds();
        long getSecs();
        unsigned long getNextInterrupt();
    private:
        double clockAdjustFactor();
        TimeZone timezone = TimeZone(0, 0, 0);
        unsigned long latest_arduino_time;
        Timestamp latest_real_time = Timestamp(2000UL, 10UL, 1UL, 0UL, 0UL, 0UL, 0UL);
        unsigned long saved_arduino_time_1;
        Timestamp saved_real_time_1 = Timestamp(2000UL, 10UL, 1UL, 0UL, 0UL, 0UL, 0UL);
        unsigned long saved_arduino_time_2;
        Timestamp saved_real_time_2 = Timestamp(2000UL, 10UL, 1UL, 0UL, 0UL, 0UL, 0UL);
};

#endif