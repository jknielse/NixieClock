#include "TinyGPS++.h"
#include "NixieDisplay.h"
#include "ClockTime.h"
#include <SD.h>
#include <SoftwareSerial.h>
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
static bool initialized = false;
static int wait_digit = 0;

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
}

void loop()
{
  while (gps_serial.available() > 0)
    if (gps.encode(gps_serial.read()))
      resyncClock();

  if (initialized){
    showTime();
  } else {
    showWaiting();
  }
}

void showTime(){
  long seconds = clock_time.getSecs();
  long s = seconds % 60;
  long m = (seconds / 60L) % 60;
  long h = (seconds / 3600L) % 24;
  nixie.push(s % 10);
  nixie.push(s / 10);
  nixie.push(m % 10);
  nixie.push(m / 10);
  nixie.push(h % 10);
  nixie.push(h / 10);
  nixie.show();
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
  delay(170);
  wait_digit++;
  wait_digit = wait_digit % 10;
}

union {
  double d;
  byte ar[4];
} doublething;

union {
  int i;
  byte ar[2];
} intthing;

float readDouble(File file) {
  for (int i=0; i< 4; i++) doublething.ar[i] = file.read();
  return doublething.d;
}

int readInt(File file) {
  for (int i=0; i< 2; i++) intthing.ar[i] = file.read();
  return intthing.i;
}

int timezoneOffsetFromLocation(double lat, double lon){
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
    }
  }
  timezone_file.close();
  showNum(123456);
  delay(500);
  showNum(zone);
  delay(1000);
  
  return zone;

  //at each hash index we need to store 100 potential timezone boundaries, and 6 bytes for each one.
  //the first 4 bytes will be a double specifying the longitudinal boundary between timezones.
  //the next 2 bytes will be an int specifying which timezone has been entered.
  return 0;
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

  if (gps.time.isValid() && saved_year)
  {
    clock_time.setTime(Timestamp(saved_year, saved_month, saved_day, gps.time.hour(), gps.time.minute(), gps.time.second(), gps.time.centisecond()), millis());
    initialized = true;
  }

  if (gps.location.isValid()) {
    timezoneOffsetFromLocation(37.7589, -122.4166);
  }
  // Timezone stuff goes here
}

