#ifndef _system_H
#define _system_H

#include <Arduino.h>
#include <TimerOne.h>
#include <LowPower.h>
#include "radio.h"
#include "interface.h"

#define BAT A0
#define IRQ 3

#define INTERVAL 1000 //定时器中断触发时间间隔

extern volatile uint8_t current_STATUS;
extern bool alarm[5];
extern uint8_t keyStatus;
extern volatile uint8_t duriation;

void system_init();
uint8_t bat_voltage();
uint8_t BatPercent();
void rec_isr();
void time_isr();
void blink_block(uint8_t pin, uint8_t t, uint8_t count);
void Powerdown(unsigned long m, uint8_t p); //ms,%
void setConfig();
uint8_t configGEN(bool f);

#endif
