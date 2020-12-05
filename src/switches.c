#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"

char super_state;
char pState;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);   // if switch 1, sense 0
  P2IES &= (p2val | ~SWITCHES);  // if switch 0, sense 1 
  return p2val;
}

void switch_init()
{
  P2REN |= SWITCHES;
  P2IE  |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  led_modify();
}

void switch_IH()                //Switch handler
{
  char p2val = switch_update_interrupt_sense();
  pState = super_state;
  
  if ( (p2val & SW1) == 0)      // S1
    super_state = 1;
  else if ( (p2val & SW2) == 0) // S2
    super_state = 2;
  else if ( (p2val & SW3) == 0) // S3
    super_state = 3;
  else if ( (p2val & SW4) == 0) // S4
    super_state = 4;
}
