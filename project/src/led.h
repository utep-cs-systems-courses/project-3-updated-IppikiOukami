#ifndef led_included
#define  led_included
#include <msp430.h>


#define LED_RED BIT0                                       // P1.0
#define LED_GREEN BIT6                                     // P1.6
#define LEDS (BIT0 | BIT6)

void led_init();                                           // Initialize LEDs
void led_modify();                                         // Updates LEDs

extern unsigned char leds_changed, green_power, red_power; // more flags

#endif
