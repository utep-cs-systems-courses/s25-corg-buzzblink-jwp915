#ifndef SWITCHES_INCLUDED
#define SWITCHES_INCLUDED

// Definitions for main switch on Port 1
#define SW1 BIT3              // SW1 is connected to P1.3
#define SWITCHES SW1          // Only one switch used on Port 1

// Definitions for external switches on Port 2
#define EXP_SWITCH (BIT0 | BIT1 | BIT2 | BIT3)
#define S1 BIT0
#define S2 BIT1
#define S3 BIT2
#define S4 BIT3

// Function declarations
void switch_init();            // Initialize Port 1 switch
void switch_init_2();          // Initialize Port 2 switches
void switch_sense();           // Set interrupt edge for Port 2
void switch_interrupt_handler(); // Handle Port 1 switch interrupt

// External switch state variables
extern char switch_state_down;      // Non-zero if SW1 is pressed
extern char switch_state_changed;   // Set when switch state changes

#endif // SWITCHES_INCLUDED
