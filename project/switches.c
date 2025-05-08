#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "incrementing.h"

char switch_state_down = 0;
char switch_state_changed = 0;

/**
 * Update switch interrupt edge sensitivity to detect changes.
 * Returns the current value of P1IN.
 */
static char switch_update_interrupt_sense() {
  char p1val = P1IN;
  P1IES |= (p1val & SWITCHES);     // If switch is up, detect falling edge
  P1IES &= (p1val | ~SWITCHES);    // If switch is down, detect rising edge
  return p1val;
}

/**
 * Initialize switches on Port 1 (SW1, SW2, etc.)
 */
void switch_init() {
  P1REN |= SWITCHES;     // Enable pull-up/pull-down resistors
  P1OUT |= SWITCHES;     // Use pull-up resistors
  P1DIR &= ~SWITCHES;    // Set switches as input
  P1IE |= SWITCHES;      // Enable interrupts
  switch_update_interrupt_sense();
}

/**
 * Configure interrupt edge select for EXP_SWITCH on Port 2
 */
void switch_sense() {
  P2IES |= EXP_SWITCH;
}

/**
 * Initialize external switch on Port 2
 */
void switch_init_2() {
  P2REN |= EXP_SWITCH;         // Enable resistor
  P2OUT |= EXP_SWITCH;         // Use pull-up resistor
  P2DIR &= ~EXP_SWITCH;        // Set as input
  P2IE |= EXP_SWITCH;          // Enable interrupt
}

/**
 * Handle switch interrupt on Port 1
 */
void switch_interrupt_handler() {
  char p1val = switch_update_interrupt_sense();
  switch_state_down = (p1val & SW1) ? 0 : 1;  // Active low logic
  switch_state_changed = 1;
}
