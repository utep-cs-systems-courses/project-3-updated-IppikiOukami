#include <msp430.h>
#include <libTimer.h>
#include "switches.h"
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "led.h"

short rds = 1;
short pState = 0;

u_char midX = screenWidth/2 + 1;
u_char midY = screenHeight/2 + 1;

void wdt_c_handler()
{
  static int s1 = 0;
  static int s2 = 0;
  static int s = 0;
  static int ctr = 0;

  ctr++;

  if(ctr == 250){
    ctr = 0;
    rds = 1;
  }
  if(super_state == 1 && ++s1 == 125){
    state_advance();
    s1 = 0;
  }else if(super_state == 2){
    if((++s2 % 25) == 0) buzzer_advance();
    if(s2 == 250){
      state_advance();
      s2 = 0;
    }
  }else{
    state_advance;
  }
}

void main()
{
  led_init();
  P1OUT |= LED_GREEN; // to show CPU activity
  configureClocks();

  lcd_init();
  buzzer_init();
  switch_init();

  enableWDTInterrupts();
  or_sr(0x08);  // GIE interrupts enabled
  clearScreen(COLOR_WHITE);

  while(1){
    if(rds == 1){
      rds = 0;
    
      if(super_state == 1){}
      else if(super_state == 2){}
      else if(super_state == 3){}
      else if(super_state == 4){}
    }
    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}
