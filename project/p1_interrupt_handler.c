#include <msp430.h>
#include "led.h"

//Interrupt Service Routine for Port 1 (handles switch press)
void __interrupt_vec(PORT1_VECTOR) Port_1() {
  if (P1IFG & SWITCHES) {              //Check if the interrupt was caused by SWITCHES
    P1IFG &= ~SWITCHES;                //Clear the interrupt flags for SWITCHES
    switch_interrupt_handler();        //Call the switch handler
  }
}
