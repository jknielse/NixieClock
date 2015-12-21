#ifndef ClockTime_h
#define ClockTime_h

#include "Arduino.h"

class ClockTime
{
  public:
    ClockTime();
    void setTime(unsigned long hours, unsigned long mins, unsigned long secs, unsigned long centisecs);
    void setOffset(long secs);
    long getSecs();
  private:
    unsigned long arduino_time_millis;
    unsigned long total_centisecs;
    long offset_secs;
};

#endif