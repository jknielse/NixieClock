#include <avr/interrupt.h> 
#include <avr/io.h> 
#include "Arduino.h"

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

/* Definitions for setting and clearing register bits
*  See http://www.sigterm.de/projects/sens-o-nuts/Dokumentation/atmel/libc/group__avr__sfr.html */

int receiveroutputenable = 3;   
/* receiver output enable (pin2) on the max485.  
*  will be left low to set the max485 to receive data. */

int driveroutputenable = 4;     
/* driver output enable (pin3) on the max485.  
*  will left low to disable driver output. */

int rxpin = 0;                  // serial receive pin, which takes the incoming data from the MAX485.

unsigned long baud = 9600; 
unsigned long clockspeed = F_CPU; 
/* F_CPU is a predefined constant equal to the clock speed of the microcontroller.
*  for the Arduino duomilanove it is 16000000.
*  I'm going to dump it into clockspeed because I'm worried about it being a signed long,
*  which could screw up the bitwise math I'm going to do on baudprescale, maybe. */

unsigned long baudprescale;     
/* The baud prescale that will be loaded into the 
*  UBRR0H and UBRR0L registers to set the USART baud rate */


volatile int i = 0;           //dummy variable for for() loops, etc.
volatile byte ReceivedByte = 0; //holds the incoming byte from the receive buffer.

void (*serCallback)(byte);

void setCallback(void (*f)(byte)) {
    serCallback = f;
}

void startSerial() {
    pinMode(receiveroutputenable, OUTPUT);
    pinMode(driveroutputenable, OUTPUT);
    digitalWrite(receiveroutputenable, LOW);
    digitalWrite(driveroutputenable, LOW);    //sets pins 3 and 4 to low to enable reciever mode on the MAX485.

    pinMode(rxpin, INPUT);  //sets serial pin to receive data

    baudprescale = (((clockspeed / (baud * 16UL))) - 1); //

    cli();  //disable interrupts while initializing the USART

    sbi(UCSR0A, TXC0);
    cbi(UCSR0A, FE0);
    cbi(UCSR0A, DOR0);
    cbi(UCSR0A, UPE0);
    cbi(UCSR0A, U2X0); //
    cbi(UCSR0A, MPCM0);
    /* set transfer complete flag (TXC0 = 1).
    *  clear Frame Error flag (FE0 = 0).   
    *  clear Data overrun flag (DOR0 = 0).
    *  clear Parity overrun flag (UPE0 = 0).
    *  disable doubling of USART transmission speed (U2X0 = 0).  
    *  Disable Multi-Processor Communication Mode-- whatever that is. (MCPM0 = 0)  */

    sbi(UCSR0B, RXCIE0);
    cbi(UCSR0B, TXCIE0);
    cbi(UCSR0B, UDRIE0);
    sbi(UCSR0B, RXEN0);
    sbi(UCSR0B, TXEN0);
    cbi(UCSR0B, UCSZ02);
    /* Enable Receive Interrupt (RXCIE0 = 1).
    *  Disable Tranmission Interrupt (TXCIE = 0).
    *  Disable Data Register Empty interrupt (UDRIE0 = 0). 
    *  Enable reception (RXEN0 = 1).
    *  Enable transmission (TXEN0 = 1). 
    *  Set 8-bit character mode (UCSZ00, UCSZ01, and UCSZ02 together control this, 
    *  But UCSZ00, UCSZ01 are in Register UCSR0C). */

    cbi(UCSR0C, UMSEL00);
    cbi(UCSR0C, UMSEL01);
    cbi(UCSR0C, UPM00);
    cbi(UCSR0C, UPM01);
    sbi(UCSR0C, USBS0);
    sbi(UCSR0C, UCSZ00);
    sbi(UCSR0C, UCSZ01);
    cbi(UCSR0C, UCPOL0);
    /* USART Mode select -- UMSEL00 = 0 and UMSEL01 = 0 for asynchronous mode.
    *  disable parity mode -- UPM00 = 0 and UPM01 = 0. 
    *  Set USBS = 1 to configure to 2 stop bits per DMX standard.  The USART receiver ignores this 
    *  setting anyway, and will only set a frame error flag if the first stop bit is 0.  
    *  But, we have to set it to something.
    *  Finish configuring for 8 data bits by setting UCSZ00 and UCSZ01 to 1.  
    *  Set clock parity to 0 for asynchronous mode (UCPOL0 = 0). */

    UBRR0L = baudprescale; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register 
    UBRR0H = (baudprescale >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register 
    // ***note to self: at some point add a command to write UBRR0H high bits to 0 per datasheet for "future compatibility"

    sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed 
}

ISR(USART_RX_vect){
    ReceivedByte = UDR0;  
    serCallback(ReceivedByte);
}
