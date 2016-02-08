#include "TinyGPS++.h"
#include "NixieDisplay.h"
#include "ClockTime.h"
#include <SD.h>
#include <SoftwareSerial.h>
#include <TimerOne.h>
#include "Time.h"

//static const int GPSRX = 4, GPSTX = 3;
static const int GPSRX = 8, GPSTX = 9;
static const int NIXPROP = 5, NIXCLK = 6, NIXDATA = 7;
static const int SDCS = 4;

static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial gps_serial(GPSRX, GPSTX);
NixieDisplay nixie(NIXPROP, NIXCLK, NIXDATA);
ClockTime clock_time;
static bool initialized_time = false;
static bool initialized_timezone = false;
static int wait_digit = 0;
static unsigned long next_interrupt = 0;

void setup()
{
  gps_serial.begin(GPSBaud);
  nixie.push(10);
  nixie.push(10);
  nixie.push(10);
  nixie.push(10);
  nixie.push(10);
  nixie.push(10);
  nixie.show();

  if (!SD.begin(SDCS)) {
    showNum(111111);
    while (1) {
      //just hang so that the issue can be diagnosed
    }
  }

  Timer1.initialize(200000);
  Timer1.attachInterrupt(timeInterrupt);
}

void loop()
{
  while (gps_serial.available() > 0)
    if (gps.encode(gps_serial.read()))
      resyncClock();
}

void timeInterrupt(void) {
  if (millis() - next_interrupt > 0) {
    if (initialized_time && initialized_timezone){
      showTime();
    } else {
      showWaiting();
    }
  }
}

void showTime(){
  setTime(clock_time.localTime());
  int s = second();
  int m = minute();
  int h = hour();
  nixie.push(s % 10);
  nixie.push(s / 10);
  nixie.push(m % 10);
  nixie.push(m / 10);
  nixie.push(h % 10);
  nixie.push(h / 10);
  nixie.show();
  next_interrupt = clock_time.getNextInterrupt();
}

void showNum (long num){
  for (int i = 0; i < 6; i++) {
    nixie.push(num % 10);
    num = num / 10;
  }
  nixie.show();
}

void showWaiting(){
  for (int i = 0; i < 6; i++){
    if (i == wait_digit){
      nixie.push(0);
    } else {
      nixie.push(10);
    }
  }
  nixie.show();
  wait_digit++;
  wait_digit = wait_digit % 10;
  next_interrupt += 130;
}

union {
  double d;
  byte ar[4];
} doublething;

union {
  int i;
  byte ar[2];
} intthing;

union {
  long l;
  byte ar[4];
} longthing;

long readLong(File file) {
  for (int i=0; i< 4; i++) longthing.ar[i] = file.read();
  return longthing.l;
}

float readDouble(File file) {
  for (int i=0; i< 4; i++) doublething.ar[i] = file.read();
  return doublething.d;
}

int readInt(File file) {
  for (int i=0; i< 2; i++) intthing.ar[i] = file.read();
  return intthing.i;
}

TimeZone timezoneFromLocationAndTime(double lat, double lon, long unix_time){
  //First, we'll convert the latitude into a hash that will be
  //used to index into a file on the SD card:
  //For roughly 10m accuracy, we'll look at 10,000ths of a degree
  //and take the nearest integer to be our hash.

  unsigned long sd_seek = ((lat - 90.0) / -(180.0 / 4194304.0)) - 1UL;
  sd_seek = sd_seek * 840UL;
  int zone = 0;
  File timezone_file = SD.open("timezone.hsh");
  if (timezone_file.size() < sd_seek) {
    showNum(222222);
    while (1) {
      //just hang so that the issue can be diagnosed
    }
  }
  
  if (!timezone_file.seek(sd_seek)) {
    showNum(333333);
    while (1) {
      //just hang so that the issue can be diagnosed
    }
  } else {
    int lastZone = 0;
    while (true) {
      double zonelon = readDouble(timezone_file);
      int zonenum = readInt(timezone_file);
      if ((zonelon > lon) || (zonelon < -900.0)) {
        zone = lastZone;
        break;
      }
      lastZone = zonenum;
    }
  }
  timezone_file.close();

  String filestring = "";
  filestring += zone;
  filestring += ".tfl";

  File timezone_info_file = SD.open(filestring);
  long offset = readLong(timezone_info_file);
  long transition_time = LONG_MAX;
  long transition_offset = 0;
  while (transition_time > 0) {
      transition_time = readLong(timezone_info_file);
      transition_offset = readLong(timezone_info_file);
      if (transition_time > unix_time) {
          break;
      }
      offset = transition_offset;
  }
  timezone_info_file.close();
  return TimeZone(offset, transition_time, transition_offset);
}

long saved_year = 0;
long saved_month = 0;
long saved_day = 0;

void resyncClock()
{
  if (gps.date.isValid()){
    saved_year = gps.date.year();
    saved_month = gps.date.month();
    saved_day = gps.date.day();
  }

  if (gps.time.isValid() && saved_year && gps_serial.available() < 10)
  {
    noInterrupts();
    clock_time.setTime(Timestamp(saved_year, saved_month, saved_day, gps.time.hour(), gps.time.minute(), gps.time.second(), gps.time.centisecond()), millis());
    interrupts();
    initialized_time = true;
  }

  if (gps.location.isValid() && initialized_time) {
    clock_time.setTimeZone(timezoneFromLocationAndTime(gps.location.lat(), gps.location.lng(), clock_time.unixTime()));
    initialized_timezone = true;
  }
  // Timezone stuff goes here
}

