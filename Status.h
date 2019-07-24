#ifndef _Status_H
#define _Status_H

#include <Arduino.h>
#include "system.h" //设备外设，难分类的丢这
#include "radio.h" //无线相关代码
#include "key.h"  //按键代码

extern uint8_t keyState[]; //按键状态
extern uint8_t rfStatus; //无线状态
extern bool mute;
extern unsigned long power_t;

extern uint8_t keyDective(uint8_t sw); //按键读取函数
extern bool radioRec(); //接收
extern void radioPair(); //配对函数
extern void Alarm(); //报警函数
extern void writeConfig(unsigned int addr,uint8_t config);
extern void PowerSave(unsigned long m, uint8_t p); //ms,%
extern void writeConfig(unsigned int addr,uint8_t config);
extern uint8_t configGEN(bool f);

#define STATUS_STD 0 //标准状态主要读取外设轮询输出
#define STATUS_MSG 1 //信息接收
#define STATUS_PAIR 2 //配对

void DO_STATUS_std();
void DO_STATUS_msg();
void DO_STATUS_pair();

#endif
