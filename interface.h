#ifndef _interface_H
#define _interface_H

#include "Arduino.h"
#include "key.h"
#include "Status.h"

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
#define LEFT 1
#define MID 0
#define RIGHT 2

extern bool ispair[];
extern bool alarm[];

void interface_init();
void Boot_Lantern();
void sw_press();
void Alarm();
uint8_t led_set(bool ispair[]);
void led_pair();

#endif
