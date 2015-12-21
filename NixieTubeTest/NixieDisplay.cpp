/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "NixieDisplay.h"

NixieDisplay::NixieDisplay(int prop_pin, int clk_pin, int data_pin)
{
    _PROP = prop_pin;
    _CLK = clk_pin;
    _DATA = data_pin;

    pinMode(_PROP, OUTPUT);
    pinMode(_CLK, OUTPUT);
    pinMode(_DATA, OUTPUT);
}

void NixieDisplay::push(int num)
{
    for(int i = 0; i < 4; i++){
        digitalWrite(_DATA, num % 2);
        num = num/2;
        delayMicroseconds(_SPD);
        clk();
    }
}

void NixieDisplay::clk(){
    digitalWrite(_CLK, HIGH);
    delayMicroseconds(_SPD);
    digitalWrite(_CLK, LOW);
    delayMicroseconds(_SPD);
}

void NixieDisplay::show()
{
    digitalWrite(_PROP, HIGH);
    delayMicroseconds(_SPD);
    digitalWrite(_PROP, LOW);
    delayMicroseconds(_SPD);
}
