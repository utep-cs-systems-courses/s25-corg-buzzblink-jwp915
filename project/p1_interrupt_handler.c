#include <msp430.h>
#include "switches.h"
#include "incrementing.h"
#include "buzzer.h"
#include "led.h"

// Port 1 Interrupt Service Routine: handles SWITCHES (e.g., SW1 on P1.3)
void __interrupt_vec(PORT1_VECTOR) Port_1() {
  if (P1IFG & SWITCHES) {         // Did a button on Port 1 cause this interrupt?
    P1IFG &= ~SWITCHES;           // Clear the interrupt flag
    switch_interrupt_handler();   // Call the switch handler
  }
}

// Port 2 Interrupt Service Routine: handles S1–S4 (P2.0 to P2.3)
void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & BIT0) {             // S1 pressed
    P2IFG &= ~BIT0;
    was_Pressed = 1;
    change_State(0);
  }

  if (P2IFG & BIT1) {             // S2 pressed
    P2IFG &= ~BIT1;
    was_Pressed = 0;
    play_Tune = 0;
    change_State(1);
  }

  if (P2IFG & BIT2) {             // S3 pressed
    P2IFG &= ~BIT2;
    play_Tune = 1;
    change_State(2);
  }

  if (P2IFG & BIT3) {             // S4 pressed
    P2IFG &= ~BIT3;
    change_State(3);
  }
}

// Watchdog Timer Interrupt: used for periodic updates (250Hz)
void __interrupt_vec(WDT_VECTOR) WDT() {
  s2_SM();  // State machine for Port 2 behavior

  if (was_Pressed != 1) {
    buzzer_Update();  // Normal buzzer behavior
  }

  if (was_Pressed == 1 && play_Tune == 1) {
    timing_BPM();     // Play metronome or beat if needed
    // s3_SM_Measures(measures);  // Uncomment if measure state machine needed
  }
}
