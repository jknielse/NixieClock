#ifndef ClockTime_h
#define ClockTime_h

#include "Arduino.h"

class Timestamp
{
    public:
        Timestamp(unsigned long year, unsigned long month, unsigned long day, unsigned long hours, unsigned long mins, unsigned long secs, unsigned long centisecs);
        unsigned long getDays();
        unsigned long getMilliseconds();
        friend long operator-(Timestamp t1, Timestamp t2);
    private:
        unsigned long days;
        unsigned long msecs;
};

class ClockTime
{
    public:
        ClockTime();
        void setTime(Timestamp real_time, unsigned long arduino_time);
        void setOffset(long secs);
        long getSecs();
    private:
        double clockAdjustFactor();
        unsigned long latest_arduino_time;
        Timestamp latest_real_time = Timestamp(2000UL, 10UL, 1UL, 0UL, 0UL, 0UL, 0UL);
        unsigned long saved_arduino_time_1;
        Timestamp saved_real_time_1 = Timestamp(2000UL, 10UL, 1UL, 0UL, 0UL, 0UL, 0UL);
        unsigned long saved_arduino_time_2;
        Timestamp saved_real_time_2 = Timestamp(2000UL, 10UL, 1UL, 0UL, 0UL, 0UL, 0UL);
        long offset_secs;
};

#endif