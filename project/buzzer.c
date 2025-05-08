#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "incrementing.h"
#include "led.h"
#include "switches.h"

// === Initialize the Buzzer on P2.6 ===
void buzzer_init() {
  /*
    Direct Timer A output "TA0.1" to P2.6.
    From datasheet Table 21:
      - P2SEL.6 = 1
      - P2SEL.7 = 0
      - P2SEL2.6, P2SEL2.7 = 0
      - P2DIR.6 must be output
  */
  timerAUpmode();               // Set Timer A to up mode (used for PWM)
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL  &= ~BIT7;
  P2SEL  |= BIT6;
  P2DIR  |= BIT6;               // Set P2.6 as output
}

// === Set Buzzer Frequency ===
void buzzer_set_period(short cycles) {
  CCR0 = cycles;
  CCR1 = cycles >> 2;           // 25% duty cycle (approx. square wave)
}

// === Measure 1: Predefined Pattern ===
void measure_1(unsigned int notes_) {
  static unsigned int notes_play = 1;

  switch (notes_) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 7:
    case 8:
      notes_play = 1;
      break;
    case 3:
      notes_play = 6;
      break;
    case 6:
      notes_play = 5;
      break;
    default:
      buzzer_set_period(F_3);
      return;
  }

  s3_SM(notes_play);
}

// === Measure 2: Predefined Pattern ===
void measure_2(unsigned int notes_) {
  static unsigned int notes_play = 1;

  switch (notes_) {
    case 1:
      notes_play = 4;
      break;
    case 2:
    case 3:
    case 5:
    case 6:
      notes_play = 1;
      break;
    case 4:
    case 8:
      notes_play = 3;
      break;
    case 7:
      notes_play = 2;
      break;
    default:
      buzzer_set_period(F_3);
      return;
  }

  s3_SM(notes_play);
}

// === Measure 3: Predefined Pattern with Double Note in Case 3 ===
void measure_3(unsigned int notes_) {
  static unsigned int notes_play = 1;

  switch (notes_) {
    case 1:
      notes_play = 4;
      break;
    case 2:
      notes_play = 1;
      break;
    case 3:
      s3_SM(0);               // Optional rest or pause
      notes_play = 1;
      break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      notes_play = 3;
      break;
    default:
      buzzer_set_period(F_3);
      return;
  }

  s3_SM(notes_play);
}
