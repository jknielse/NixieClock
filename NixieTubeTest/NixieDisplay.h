#ifndef NixieDisplay_h
#define NixieDisplay_h

#include "Arduino.h"

class NixieDisplay
{
  public:
    NixieDisplay(int prop_pin, int clk_pin, int data_pin);
    void push(int num);
    void show();
  private:
    void clk();
    int _PROP;
    int _CLK;
    int _DATA;
    const int _SPD = 0;
};

#endif
