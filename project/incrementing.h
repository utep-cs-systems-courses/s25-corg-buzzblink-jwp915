#ifndef INCREMENTING_INCLUDED
#define INCREMENTING_INCLUDED

// === Initialization ===
void wdt_init();              // Initialize Watchdog Timer

// === Blink Timing and Updates ===
void blink_Lim();             // Set blink timing limit
void blink_Update_Green();    // Update green LED blink state
void blink_Update_Red();      // Update red LED blink state

// === Simple Blink Controls ===
void blink_green();           // Blink green LED once
void blink_red();             // Blink red LED once

// === Direct LED Control ===
void red_Control(int on);     // Turn red LED on/off
void green_Control(int on);   // Turn green LED on/off

// === Time-based Control ===
void second_control();        // Second-level timing logic
void timing_BPM();            // BPM-based metronome timing

#endif // INCREMENTING_INCLUDED
