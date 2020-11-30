#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"


static short freq = 500;                              // Initial frequency of state 2.
static short state2_status = 1;                       // Initial state for state 2

char state1()
{
  char changed = 0;
  changed = toggle_red();
  leds_changed = changed;
  led_modify();
}

// Toggles Red
char toggle_red()
{
  static char stateS1 = 1;
  if (stateS1){
    red_power = 0;                                   // if S1 is on, switch red to off
    buzzer_set_period(0);
    stateS1 = 0;
  }
  else{
    red_power = 1;                                   // if S1 is off, switch red to on
    buzzer_set_period(1000);
    stateS1 = 1;
  }
  return 1;
}

//Toggle_green not needed for this
                                                   // Pitch starts at 500 up to 5000, increases 1/10 seconds
char state2()
{
  static short stateS2 = 0;
  if (stateS2 == 1){
    state2_status = 1;
    red_power = 1;
    leds_changed = 1;
    led_modify();
    stateS2++;
  }
  else if (stateS2 == 2){
    state2_status = 0;
    red_power = 0;
    leds_changed = 1;
    led_modify();
    stateS2 = 0;
  }
  return 1;
}

// If state2_status == 1, increase pitch. Otherwise, decrease pitch.
void buzzer_advance(){
  if (state2_status) freq += 225;
  else freq -= 450;
  short period = 2000000/freq;  // 2000000 / frequency works
  buzzer_set_period(period);
}

// Dimmer
char state3()
{
  static short s3Counter = 0;
  static short stateS3 = 0;
  if (++s3Counter == 125) { stateS3++; s3Counter = 0;}
  switch (stateS3){
  case 0: dimLights(1); buzzer_set_period(0); break;
  case 1: dimLights(2); buzzer_set_period(500); break;
  case 2: dimLights(3); buzzer_set_period(1500); break;
  case 3: dimLights(4); buzzer_set_period(6000); break;
  case 4: dimLights(8); buzzer_set_period(24000); break;
  case 5: dimLights(16); buzzer_set_period(0); stateS3 = 0; break;
  }
}

void dimLights(char x){
  static short dimCount = 0;
  switch(dimCount % x){
  case 0: red_power = 1; dimCount++; break;
  case 1: red_power = 0; dimCount++; break;
  default: red_power = 0; dimCount++; break;
  }
  leds_changed = 1;
  led_modify();
}

// Turn everything off
char state4(){
  buzzer_set_period(0);
  red_power = 0;
  leds_changed = 1;
  led_modify();
  return 1;
}

// Translating this to Assembly ;P
// Changes state when super_state is changed.
/*void state_advance()
{
  char changed = 0;
  switch(super_state){
  case 1:
    changed = state1(); // Leds + Buzzer
    break;
  case 2:
    changed = state2(); // Buzzer
    break;
  case 3:
    changed = state3(); // Leds (Dim)
    break;
  case 4:
    changed = state4(); // All off
    break;
  }
  leds_changed = changed;
  led_modify();
}*/
