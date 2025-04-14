#include <msp430.h>
#include "libTimer.h"

//Configure system clocks: Set DCO to 16MHz, SMCLK = DCO/8
void configureClocks(){
  WDTCTL = WDTPW | WDTHOLD;    //Disable Watchdog Timer

  BCSCTL1 = CALBC1_16MHZ;      //Set DCO to 16 MHz
  DCOCTL  = CALDCO_16MHZ;

  BCSCTL2 &= ~SELS;            //Select DCO for SMCLK
  BCSCTL2 |= DIVS_3;           //SMCLK = DCO / 8
}

//Enable watchdog timer periodic interrupt
//Period = SMCLK / 8192
void enableWDTInterrupts(){
  WDTCTL = WDTPW       |       //Password
           WDTTMSEL    |       //Interval timer mode
           WDTCNTCL    |       //Clear watchdog counter
           1;                  //Divide SMCLK by 8192

   IE1 |= WDTIE;               //Enable WDT interrupt
}

//Configure Timer A in Up mode with toggle on CCR1
void timerAUpmode(){
  TA0CCR0  = 0;                //No capture/compare
  TA0CCR1  = 0;
  TA0CCTL1 = OUTMOD_3;         //Toggle/set mode on CCR1 (P1.6)

  TACTL = TASSEL_2 | MC_1;     //SMCLK, Up mode
}
