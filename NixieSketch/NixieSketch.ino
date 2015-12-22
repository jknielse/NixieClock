#include "TinyGPS++.h"
#include "NixieDisplay.h"
#include "ClockTime.h"
#include <SD.h>
#include <SoftwareSerial.h>

//static const int GPSRX = 4, GPSTX = 3;
static const int GPSRX = 8, GPSTX = 9;
static const int NIXPROP = 5, NIXCLK = 6, NIXDATA = 7;
static const int SDCS = 4, SDMOSI = 3, SDSCK = 2, SDMISO = 1;

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
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
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

void resyncClock()
{
  if (gps.time.isValid())
  {
    unsigned long t = millis();
    clock_time.setTime(Timestamp(gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second(), gps.time.centisecond()), t);
    initialized = true;
  }
  // Timezone stuff goes here
}

