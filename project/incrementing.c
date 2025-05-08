// Initial test: red LED always on, green LED blinks
#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "incrementing.h"
#include "buzzer.h"

// === Global Variables ===
unsigned char state_Note = 1;
unsigned char measures = 1;

static int blinkLimit = 3;
static unsigned int notes = 0;
static unsigned int measure = 1;

// === Watchdog Timer Initialization ===
void wdt_init() {
  configureClocks();
  enableWDTInterrupts();
}

// === LED Blink Update Logic ===
void blink_Update_Red() {
  static int blinkCount = 0;
  blinkCount--;
  if (blinkCount <= blinkLimit) {
    blinkCount = 7;
    red_Control(1);
  } else {
    red_Control(0);
  }
}

void blink_Update_Green() {
  static int blinkCount = 0;
  blinkCount++;
  if (blinkCount >= blinkLimit) {
    blinkCount = 0;
    green_Control(1);
  } else {
    green_Control(0);
  }
}

// === Simple Blink Control ===
void blink_green() {
  blink_Update_Red();   // Green "blink" maps to red LED update
}

void blink_red() {
  blink_Update_Green(); // Red "blink" maps to green LED update
}

// === LED Control Helpers ===
void green_Control(int on) {
  if (on) {
    P1OUT |= LED_RED;     // Green control maps to RED LED pin
  } else {
    P1OUT &= ~LED_RED;
  }
}

void red_Control(int on) {
  if (on) {
    P1OUT |= LED_GREEN;   // Red control maps to GREEN LED pin
  } else {
    P1OUT &= ~LED_GREEN;
  }
}

// === Time-Based Blink Limit Update ===
void second_Update() {
  static int countsec = 0;
  countsec++;
  if (countsec >= 250) {   // 250 calls per second
    countsec = 0;
    blink_Lim();           // Modify blink rate
  }
}

void blink_Lim() {
  blinkLimit++;
  if (blinkLimit >= 8)
    blinkLimit = 0;
}

// === BPM Timing & Note/Measure State Machine ===
void timing_BPM() {
  static int change_notes = 0;
  change_notes++;
  if (change_notes >= 32) {     // ~240 BPM assuming 8th notes
    change_notes = 0;
    notes++;

    if (notes >= 9) {
      notes = 0;
      measures++;
      if (measures >= 5) {
        measures = 1;
      }
    }
    s3_SM_Measures(measures, notes);
  }
}

// === Time Advance State Machines ===
void time_Adv_SM_Green() {
  blink_green();     // Run green LED logic
  second_Update();   // Keep time consistent across both
}

void time_Adv_SM_Red() {
  blink_red();       // Run red LED logic
  second_Update();   // Shared timer
}
