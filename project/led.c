#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "incrementing.h"
#include "buzzer.h"

// === Global Flags and State ===
unsigned char play_Tune = 0;
unsigned char was_Pressed = 0;
unsigned char gone_Once = 0;
unsigned char led_Flags = 0;
unsigned char state = 0;
unsigned long frqz = 3500;

// === LED Initialization ===
void led_init() {
  P1DIR |= LEDS;                  // Set LED pins as output
  switch_state_changed = 1;       // Trigger update on first run
  led_update();
}

void led_Off() {
  P1OUT &= ~LEDS;                 // Turn off both LEDs
}

// === Buzzer Control Based on Switch State ===
void buzzer_Update() {
  if (switch_state_down) {
    if (!gone_Once) {
      gone_Once++;
      frqz -= 0xC4;               // Decrease frequency
    }
    buzzer_set_period(frqz);
    if (frqz > 0x8CA2) {          // Reset if too high
      frqz = 0xDAC;
    }
  } else {
    gone_Once = 0;
    buzzer_set_period(0);
  }
  switch_state_changed = 0;
}

// === LED Update (Placeholder for advanced behavior) ===
void led_update() {
  unsigned char led_Flags = 0;
  // Placeholder logic — currently no visual feedback here
  // You may add blinking or timed transitions here if needed
}

// === LED Blink Behavior ===
void blinkers_Green() {
  P1OUT &= (0xFF - LEDS) | led_Flags;
  P1OUT &= ~LED_RED;
  time_Adv_SM_Green();
}

void blinkers_Red() {
  P1OUT &= (0xFF - LEDS) | led_Flags;
  P1OUT &= ~LED_GREEN;
  time_Adv_SM_Red();
}

// === State Machine for LED/Buzzer Modes ===
void change_State(short new_state) {
  state = new_state;
  s2_SM();
}

void s2_SM() {
  switch (state) {
    case 0:
      blinkers_Red();
      buzzer_set_period(frqz);
      break;
    case 1:
      blinkers_Green();
      break;
    case 2:
      blinkers_Red();
      break;
    case 3:
      buzzer_set_period(0); // Stop all sound
      break;
    default:
      buzzer_set_period(0); // Fallback
      if (state >= 4 || state < 0) {
        state = 0;
      }
      break;
  }
}

// === Note State Machine (Single Notes) ===
void s3_SM(unsigned int notes_play) {
  switch (notes_play) {
    case 1: buzzer_set_period(F_3); break;
    case 2: buzzer_set_period(DB_4); break;
    case 3: buzzer_set_period(D_4); break;
    case 4: buzzer_set_period(EB_4); break;
    case 5: buzzer_set_period(E_4); break;
    case 6: buzzer_set_period(F_4); break;
    default: buzzer_set_period(0); break;
  }
}

// === Measure Control Logic ===
void s3_SM_Measures(unsigned int measures_, unsigned int notes_) {
  switch (measures_) {
    case 1:
    case 3:
      measure_1(notes_);
      break;
    case 2:
      measure_2(notes_);
      break;
    case 4:
      measure_3(notes_);
      break;
    default:
      buzzer_set_period(1000); // Fallback frequency
      break;
  }
}
