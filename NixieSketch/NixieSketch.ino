#include "TinyGPS++.h"
#include "NixieDisplay.h"
#include <SD.h>
#include <SoftwareSerial.h>

//static const int GPSRX = 4, GPSTX = 3;
static const int GPSRX = 9, GPSTX = 8;
static const int NIXPROP = 2, NIXCLK = 3, NIXDATA = 4;
static const int SDCD = 10, SDMOSI = 11, SDSCK = 12, SDMISO = 13;

static const uint32_t GPSBaud = 9600;

//TinyGPSPlus gps;
//SoftwareSerial gps_serial(GPSRX, GPSTX);
NixieDisplay nixie(NIXPROP, NIXCLK, NIXDATA);


void setup()
{
  //Serial.begin(115200);
  //gps_serial.begin(GPSBaud);
}

void loop()
{
  for(long i = 999999; i > 0; i--){
    long t = i;
    for(int n = 0; n < 6; n++){
      nixie.push(t % 10);
      t = t / 10;
    }
    nixie.show();
  }
  /*
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gps_serial.available() > 0)
    if (gps.encode(gps_serial.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }*/
}

/*
void displayInfo()
{
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}*/
