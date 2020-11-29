#include <msp430.h>
#include "switches.h"

void __interrupt_vec(PORT2_VECTOR) Port_2(){  // Use P1 at S2
  if(P2IFG & SWITCHES){                       
    P2IFG &= ~SWITCHES;                      // clear interrupts (SW)
    switch_IH();
  }
}
