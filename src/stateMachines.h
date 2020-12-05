#ifndef stateMachines_included
#define stateMachine_included

extern char lcdState;

void state_advance();
char toggle_red();
void buzzer_advance();
void dimLights(char x);
void lcd_state(int color);

#endif
