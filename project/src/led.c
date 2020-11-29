#include <msp430.h>
#include "led.h"

unsigned char red_power = 0, green_power = 0, leds_changed = 0;

static char r_val[] = {0, LED_RED}, g_val[] = {0, LED_GREEN}; // use indexing rather than mult var

void led_init(){
  P1DIR |= LEDS;                                              // Initialize P1DIR with output Leds
  leds_changed = 1;
  led_modify();
}

void led_modify(){
  if (leds_changed){
    char indicator = r_val[red_power] | g_val[green_power];

    P1OUT &= (255 - LEDS) | indicator;                       // set to off if on
    P1OUT |= indicator;                                      // set to on if off
    leds_changed = 0;
  }
}
