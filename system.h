#ifndef _system_H
#define _system_H

#include "Arduino.h"
#include "radio.h"
#include "interface.h"

#define BAT A0
#define IRQ 3

/*
 * LED的三种状态以及闪烁间隔
 */
#define LED_STATUS_BRIGHT 0
#define LED_STATUS_DARK 1
#define LED_DELAY_SLOW 5000 //闪烁间隔
 
extern volatile uint8_t current_STATUS;
extern bool alarm[5];
extern uint8_t keyStatus;

bool system_init();
uint8_t bat_voltage();
void isr();

#endif
