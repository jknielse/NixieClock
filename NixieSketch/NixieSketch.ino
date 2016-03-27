#include "TinyGPS++.h"
#include "NixieDisplay.h"
#include "ClockTime.h"
#include <SD.h>
#include <TimerOne.h>
#include "Time.h"
#include "InterruptSerial.h"


static const int NIXPROP = 5, NIXCLK = 6, NIXDATA = 7;
static const int SDCS = 4;

TinyGPSPlus gps;
NixieDisplay nixie(NIXPROP, NIXCLK, NIXDATA);
ClockTime clock_time;

volatile static int wait_digit = 0;
volatile static int wait_dir = -1;

volatile static bool initialized_time = false;
volatile static bool initialized_timezone = false;
volatile static bool should_do_timezone = false;
volatile static bool initialized_clock = false;
volatile static int saved_year = 0;
volatile static int saved_month = 0;
volatile static int saved_day = 0;
volatile static int saved_hour = 0;
volatile static int saved_minute = 0;
volatile static int saved_second = 0;
volatile static int saved_centisecond = 0;
volatile static unsigned long saved_millis = 0;
volatile static unsigned long last_millis = 0;
volatile static double saved_lat = 0;
volatile static double saved_lon = 0;
volatile static bool can_touch = true;
volatile static bool can_read = true;

//One thing that worked well was an 8ms timer that read one byte per interrupt.

void setup()
{
  for (int i = 0; i < 6; i++) {
    nixie.push(10);
  }
  nixie.show();

  if (!SD.begin(SDCS)) {
    err(1);
  }

  setCallback(encodeSerial);

  startSerial();

  Timer1.initialize(200000UL);
  Timer1.attachInterrupt(timeInterrupt);
}

void loop()
{
  if (initialized_timezone && (last_millis != saved_millis)) {
    can_touch = false;
    Timestamp t = Timestamp(saved_year, saved_month, saved_day, saved_hour, saved_minute, saved_second, saved_centisecond);
    can_touch = true;
    TimeZone tz = TimeZone(0, LONG_MAX, 0);
    if (should_do_timezone) {
      tz = timezoneFromLocationAndTime(saved_lat, saved_lon, clock_time.unixTime());
    }
    can_read = false;
    if (should_do_timezone) {
      clock_time.setTimeZone(tz);
    }
    clock_time.setTime(t, saved_millis);
    can_read = true;
    if (should_do_timezone) {
      initialized_clock = true;
    }
    should_do_timezone = true;
    last_millis = saved_millis;
  }
}

void err (int num) {
  noInterrupts();
  for (int i = 0; i < 6; i++) {
    nixie.push(num);
  }
  nixie.show();
  //Spin forever so the problem can be diagnosed
  while (1) {};
}

void timeInterrupt(void) {
  interrupts();
  recordData();
  if (initialized_clock){
    if (can_read) {
      showTime();
    }
  } else {
    showWaiting();
  }
}

void encodeSerial(byte b) {
  gps.encode(b);
}

void recordData() {
  if (can_touch) {
    if (gps.date.isValid()){
      saved_year = gps.date.year();
      saved_month = gps.date.month();
      saved_day = gps.date.day();
    }
    if (gps.time.isValid() && saved_year)
    {
      saved_hour = gps.time.hour();
      saved_minute = gps.time.minute();
      saved_second = gps.time.second();
      saved_centisecond = gps.time.centisecond();
      saved_millis = gps.time.lastCommitTime;
      initialized_time = true;
    }
    if (gps.location.isValid() && initialized_time) {
      saved_lat = gps.location.lat();
      saved_lon = gps.location.lng();
      initialized_timezone = true;
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
  noInterrupts();
  Timer1.setPeriod(clock_time.getNextInterrupt() * 1000UL);
  TCNT1 = 1;
  interrupts();
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

  if (wait_digit == 5 || wait_digit == 0) {
    wait_dir = -wait_dir;
  }

  wait_digit += wait_dir;
}

void showNum (long num){
  for (int i = 0; i < 6; i++) {
    nixie.push(num % 10);
    num = num / 10;
  }
  nixie.show();
}

void slowPrint (unsigned long num) {
  showNum(0);
  delay(1000);
  while (num) {
    nixie.push(num % 10);
    num = num / 10;
    nixie.show();
    delay(1000);
  }
  delay(5000);
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

union {
  unsigned long l;
  byte ar[4];
} ulongthing;

long readLong(File file) {
  for (int i=0; i< 4; i++) longthing.ar[i] = file.read();
  return longthing.l;
}

unsigned long readULong(File file) {
  for (int i=0; i< 4; i++) ulongthing.ar[i] = file.read();
  return ulongthing.l;
}

float readDouble(File file) {
  for (int i=0; i< 4; i++) doublething.ar[i] = file.read();
  return doublething.d;
}

int readInt(File file) {
  for (int i=0; i< 2; i++) intthing.ar[i] = file.read();
  return intthing.i;
}

TimeZone timezoneFromLocationAndTime(double lat, double lon, unsigned long unix_time){
  //First, we'll convert the latitude into a hash that will be
  //used to index into a file on the SD card:
  //For roughly 10m accuracy, we'll look at 10,000ths of a degree
  //and take the nearest integer to be our hash.

  unsigned long sd_seek = ((lat - 90.0) / -(180.0 / 4194304.0)) - 1UL;
  sd_seek = sd_seek * 840UL;
  int zone = 0;
  File timezone_file = SD.open(F("timezone.hsh"));
  if (timezone_file.size() < sd_seek) {
    err(2);
  }
  
  if (!timezone_file.seek(sd_seek)) {
    err(3);
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

  char filestring[9];
  int i = 9;
  int newzone = zone;
  while (zone > 0) {
    i--;
    filestring[i] = (char)((int)'0' + (zone % 10));
    zone /= 10;
  }
  int i2 = 0;
  while (i < 9) {
    filestring[i2] = filestring[i];
    i++;
    i2++;
  }
  filestring[i2] = '.';
  filestring[i2 + 1] = 't';
  filestring[i2 + 2] = 'f';
  filestring[i2 + 3] = 'l';
  filestring[i2 + 4] = 0;

  File timezone_info_file = SD.open(filestring);
  long offset = readLong(timezone_info_file);
  unsigned long transition_time = ULONG_MAX;
  long transition_offset = 0;
  int test = 0;
  while (transition_time > 0) {
      test++;
      transition_time = readULong(timezone_info_file);
      transition_offset = readLong(timezone_info_file);
      if (transition_time > unix_time) {
          break;
      }
      offset = transition_offset;
  }
  timezone_info_file.close();
  return TimeZone(offset, transition_time, transition_offset);
}

