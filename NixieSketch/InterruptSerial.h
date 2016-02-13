#include <avr/interrupt.h> 
#include <avr/io.h> 

#ifndef InterruptSerial_h
#define InterruptSerial_h

void setCallback(void (*f)(byte));
void startSerial();

#endif