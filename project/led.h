#ifndef LED_INCLUDED
#define LED_INCLUDED

#include <msp430.h>

// === LED Pin Definitions ===
#define LED_RED BIT0     // P1.0
#define LED_GREEN BIT6   // P1.6
#define LEDS (LED_RED | LED_GREEN)

// === Initialization & Update Functions ===
void led_init();         // Initialize LEDs
void led_update();       // Update LED states
void wdt_init();         // Initialize Watchdog Timer

// === LED Control Functions ===
void green_Control(int on);      // Turn green LED on/off
void red_Control(int on);        // Turn red LED on/off
void blink_green();              // Simple blink for green LED
void blink_red();                // Simple blink for red LED
void blink_Update_Green();       // Green LED blink logic
void blink_Update_Red();         // Red LED blink logic
void blinkers_Green();           // Complex blink behavior for green
void blinkers_Red();             // Complex blink behavior for red

// === State Machine Functions ===
void time_Adv_SM_Green();        // Time advance state machine for green LED
void time_Adv_SM_Red();          // Time advance state machine for red LED
void s2_SM();                    // State machine for handling switch input
void s3_SM(unsigned int input);  // State machine level 3
void s3_SM_Measures(unsigned int measures_, unsigned int notes_);
void change_State(short new_state); // Change main state
void change_Note(unsigned char new_Note); // Change current note

// === Sound / Frequency Functions ===
void buzzer_Update();            // Update buzzer logic

// === Global State Flags ===
extern unsigned char play_Tune;
extern unsigned char was_Pressed;
extern unsigned char gone_Once;
extern unsigned char state;
extern unsigned char led_Flags;
extern unsigned char leds_changed;
extern unsigned char green_led_state;
extern unsigned char red_led_state;
extern unsigned long frqz;

#endif // LED_INCLUDED
