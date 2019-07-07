#ifndef _interface_H
#define _interface_H

#include <Arduino.h>
#include "key.h"
#include "Status.h"
#include "system.h"

#include <avr/sleep.h>

#define SW1 2 //中键
#define SW2 4 //左键
#define SW3 7 //右键
#define LED0 15
#define LED1 16
#define LED2 17
#define LED3 18
#define LED4 19
#define BZ 5

#define LEFT 1
#define MID 0
#define RIGHT 2

#define C4 262
#define E4 311
#define G4 392
#define A6 1760

extern bool ispair[];
extern bool alarm[];
extern unsigned int blink_rate;
extern bool ispair[];
extern bool alarm[];

void interface_init();
void Boot_Lantern();
void sw_press();
void Alarm();
uint8_t led_set(bool ispair[]);
void led_pair();
void set_blink_rate(int f);
void BZ_alarm();
void BZ_noneAlarm();

#endif
