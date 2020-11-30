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

      static char sColor = 0;
      u_int COLOR;

      if(sColor == 1){
	COLOR = COLOR_YELLOW; sColor = 1;
      }else if(sColor = 1){
	COLOR = COLOR_GREEN; sColor = 0;
      }
      
      if(super_state == 0){
	drawString8x12(0,0,"Final Project", COLOR_WHITE,COLOR_BLACK);
      }
      else if(super_state == 1){
	drawString8x12(0,0,"Final Project", COLOR_BLACK,COLOR_BLACK);
	lcd_state(COLOR_GREEN);
	pState = 1;
      }
      else if(super_state == 2){
	drawString5x7(20,screenHeight - 10,"Buzzer",COLOR_YELLOW,COLOR_BLACK);
	lcd_state(COLOR_PINK);
	pState = 2;
      }
      else if(super_state == 3){
	drawErase();
	for (u_char r = 0; r < 6; r++){
	  for (u_char c = 0; c <= r; c++){
	    drawPixel(midX-c, midY-r-1,COLOR_WHITE);
	    drawPixel(midX-c, midY+r-(6),COLOR_WHITE);
	    drawPixel(midX+c, midY-r-1,COLOR_WHITE);
	    drawPixel(midX+c, midY+r-(6), COLOR_WHITE);
	  }
	}
	drawString5x7(20,screenHeight - 10,"Buzzer",COLOR_BLACK,COLOR_BLACK);
	drawString8x12(20,screenHeight - 10,"Dim Broke",COLOR_WHITE,COLOR_BLACK);
	pState = 3;
      }
      else if(super_state == 4){
	if(pState != 4) drawErase();
	drawString5x7(20,screenHeight - 10,"Buzzer", COLOR_BLACK,COLOR_BLACK);
	drawString8x12(20,screenHeight - 10,"Dim Broke",COLOR_BLACK,COLOR_BLACK);

	pState = 4;
      }
    }
    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}
