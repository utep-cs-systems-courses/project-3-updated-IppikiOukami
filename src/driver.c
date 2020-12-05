#include <msp430.h>
#include <libTimer.h>
#include "switches.h"
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "led.h"

short rds = 1;
static short pState = 0;

u_char midX = screenWidth/2 + 1;
u_char midY = screenHeight/2 + 1;

// if positive return true, false otherwise
int cmp_assembly(int num);

void drawTriangle(u_char col, u_char row, u_char size, u_int color)
{
  for (u_char r = 0; r < size; r++){
    for (u_char c = 0; c <= r; c++){
      drawPixel(col-c, row-r-1, color);
      drawPixel(col-c, row+r-(2*size), color);
    }
  }
}

void wdt_c_handler()
{
  static int s1 = 0;
  static int s2 = 0;
  static int ctr = 0;

  if (++ctr == 250){
    ctr = 0;
    rds = 1;
  }
  if (super_state != 3 && pState != super_state) rds = 1;
  if(super_state == 1){
    if (++s1 == 125) {
      state_advance();
      s1 = 0;
    }
  } else if (super_state == 2) {
    if ( (++s2 % 25) == 0) buzzer_advance();
    if (s2 == 250){
      state_advance();
      s2 = 0;
    }
  } else{
    state_advance();
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
  clearScreen(COLOR_BLACK);

  while(1){
    if(rds == 1){
      rds = 0;
   
      if(super_state == 0){
	drawString8x12(0,0,"Final Project", COLOR_WHITE,COLOR_BLACK);
      }
      else if(super_state == 1){
	clearScreen(COLOR_BLACK);
	lcd_state(COLOR_GREEN);
	pState = 1;
      }
      else if(super_state == 2){
	lcd_state(COLOR_PINK);
	pState = 2;
      }
      else if(super_state == 3){
	clearScreen(COLOR_BLACK);
	for (u_char r = 0; r < (midY/2); r++){
	  for (u_char c = 0; c <= r; c++){
	    drawPixel(midX-c, midY+r-(6),COLOR_YELLOW);
	    drawPixel(midX-c, midY-r-1,COLOR_WHITE);
	  }
	}
	pState = 3;
      }
      else if(super_state == 4){
	if(pState != 4) clearScreen(COLOR_BLUE);
	drawString8x12(0,0,"2 + 2 = Fish",COLOR_WHITE,COLOR_BLUE);
	if(cmp_assembly(2) != 0){
	  drawString8x12(midX,midY,"2 > 0",COLOR_BLACK,COLOR_BLUE);
	}
	if(cmp_assembly(-2) == 0){
	  drawString8x12(midX,midY-20,"-1 < 0",COLOR_RED,COLOR_BLUE);
	}
	pState = 4;
      }
    }
    P1OUT &= ~LED_GREEN; // Turn off green (CPU Sleep)
    or_sr(0x10);         // GIE
    P1OUT |= LED_GREEN;  // Turn on green LED (wake)
  }
}
