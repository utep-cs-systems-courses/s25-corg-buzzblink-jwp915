#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void){
  configureClocks();              //Set DCO and SMCLK
  
  //Set LED pins as output and turn them off
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;

  //Configure switch input with pull-up, interrupt enabled
  P1REN |= SWITCHES;              //Enable resistor
  P1OUT |= SWITCHES;              //Pull-up resistor
  P1DIR &= ~SWITCHES;             //Set switch pins as input
  P1IE  |= SWITCHES;              //Enable interrupt on switch

  or_sr(0x18);                    //Enable CPU interrupts (GIE)
}

//Switch interrupt handler
void switch_interrupt_handler(){
  char p1val = P1IN;              //Read port 1 input

  //Update interrupt edge sense:
  //If switch is up (high), detect falling edge (press)
  //If switch is down (low), detect rising edge (release)
  P1IES |=  (p1val & SWITCHES);   //If switch is up, sense down
  P1IES &= (p1val | ~SWITCHES);   //If switch is down, sense up

  //Control LEDs:
  //Switch up = red LED on
  //Switch down = green LED on
  if (p1val & SW1){
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
  } else {
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  }
}
