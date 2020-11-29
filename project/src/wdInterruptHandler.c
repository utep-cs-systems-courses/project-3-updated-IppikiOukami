#include <msp430.h>
#include "stateMachines.h"

char super_state = 0;

void __interrupt_vec(WDT_VECTOR) WDT(){/* 250 interrupts/sec */
  static char s1Count = 0;
  static char s2Count = 0;

  // Interrupts once every half a sec.
  if (super_state == 1){
    if (++ s1Count == 125){
      state_advance();
      s1Count = 0;
    }
  }
  else if (super_state == 2){ // Interrupts buzzer every 1/10 of a second.
    if ( (++ s2Count % 25) == 0) buzzer_advance();
    if (s2Count == 250){ // Change state every second.
      state_advance();
      s2Count = 0;
    }
  }
  else { // State 3 and 4, Interrupt every 1/250 of a sec.
    state_advance();
  }
}
