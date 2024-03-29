#ifndef _system_H
#define _system_H

#include <Arduino.h>
#include <TimerOne.h>
#include "radio.h"
#include "interface.h"

#define BAT A0
#define IRQ 3

#define INTERVAL 1000 //定时器中断触发时间间隔（μs）
#define POWERDOWN_T 900000 //进入低功耗模式时间（ms）
#define WAKEUP_T_SW 300000 //中键唤醒保持时间（ms）
#define WAKEUP_T_IRQ 60000 //消息唤醒保持时间（ms）

extern volatile uint8_t current_STATUS;
extern bool alarm[5];
extern uint8_t keyStatus;
extern volatile uint8_t duriation;

extern void interface_init();
extern void Boot_Lantern(uint8_t c);
extern void sw_press();
extern void led_pair();
extern uint8_t readConfig(unsigned int addr);

void system_init();
uint8_t bat_voltage();
uint8_t BatPercent();
void rec_isr();
void sw_isr();
void time_isr();
void blink_block(uint8_t pin, uint8_t t, uint8_t count);
void PowerSave(unsigned long m, uint8_t p); //ms,%
void setConfig();
uint8_t configGEN(bool f);

#endif
