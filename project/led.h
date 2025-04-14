#ifndef LED_INCLUDED
#define LED_INCLUDED

//LED definitions for P1.0 and P1.6
#define LED_RED     BIT0    //P1.0
#define LED_GREEN   BIT6    //P1.6
#define LEDS        (LED_RED | LED_GREEN)

//Switch definition for P1.3
#define SW1         BIT3    //P1.3
#define SWITCHES    SW1

//Function prototype for switch interrupt handler
void switch_interrupt_handler();

#endif //LED_INCLUDED
