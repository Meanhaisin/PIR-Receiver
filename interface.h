#ifndef _interface_H
#define _interface_H

#include "Arduino.h"

#include <avr/sleep.h>

#define SW1 2
#define SW2 4
#define SW3 7
#define LED1 15
#define LED2 16
#define LED3 17
#define LED4 18
#define LED5 19
#define BZ 5

void interface_init();
void Boot_Lantern();

#endif
