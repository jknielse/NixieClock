#include "Arduino.h"
#include "ClockTime.h"

ClockTime::ClockTime()
{
    arduino_time_millis = 0;
    total_centisecs = 0;
    offset_secs = 0;
}

void ClockTime::setTime(unsigned long hours, unsigned long mins, unsigned long secs, unsigned long centisecs) {
    arduino_time_millis = millis();
    total_centisecs = (((hours * 60UL) + mins) * 60UL + secs) * 100UL + centisecs;
}

void ClockTime::setOffset(long secs){
    offset_secs = secs;
}

// seconds since start of day
long ClockTime::getSecs(){
    long current_time = total_centisecs * 10UL + millis() - arduino_time_millis + offset_secs * 1000L;
    return current_time/1000UL;
}

