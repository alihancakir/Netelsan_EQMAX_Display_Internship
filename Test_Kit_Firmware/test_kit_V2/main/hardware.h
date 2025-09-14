#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <stdbool.h>

void config_gpio(void);

bool menu_button_state();
bool move_button_state();
bool back_button_state();

#endif 
