#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "incrementing.h"
#include "buzzer.h"

void main(void) 
{
  // === Peripheral Initialization ===
  switch_init();       // Initialize Port 1 switches
  switch_init_2();     // Initialize Port 2 switches
  buzzer_init();       // Setup buzzer on P2.6
  led_init();          // Setup LEDs on P1.0 and P1.6
  wdt_init();          // Setup Watchdog Timer for periodic interrupts

  // === Enter Low Power Mode with Interrupts Enabled ===
  or_sr(0x18);          // CPU off, GIE on (Low Power Mode 0)
}
