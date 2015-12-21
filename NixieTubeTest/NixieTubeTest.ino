#include "NixieDisplay.h"

//static const int GPSRX = 4, GPSTX = 3;
static const int GPSRX = 9, GPSTX = 8;
static const int NIXPROP = 5, NIXCLK = 6, NIXDATA = 7;
static const int SDCS = 4, SDMOSI = 3, SDSCK = 2, SDMISO = 1;

static const uint32_t GPSBaud = 9600;

NixieDisplay nixie(NIXPROP, NIXCLK, NIXDATA);


void setup()
{
}

void loop()
{
    nixie.push(1);
    nixie.push(2);
    nixie.push(3);
    nixie.push(4);
    nixie.push(5);
    nixie.push(6);
    nixie.show();
    delay(1000);
}
