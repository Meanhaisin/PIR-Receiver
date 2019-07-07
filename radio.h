#ifndef _radio_H
#define _radio_H

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "system.h"
#include "ROM.h"
#include "Status.h"
#include "key.h"
#include "interface.h"

#define CE 9
#define CSN 10

#define RF_STATUS_START_PAIR 0
#define RF_STATUS_PAIRING 1

#define PAY_LOAD_SIZE_STD 1 //标准发射负载大小
#define PAY_LOAD_SIZE_PAIR 5 //配对发射负载大小
#define REC_READINGPIPE_OFFSITE 1 //接收管道偏移
#define PAIR_READINGPIPE 1 //配对管道

extern uint8_t sw_status[];
extern uint8_t pos;

const byte pair_pipe[5] = {'P', 'p', 'a','i' ,'r'}; //配对默认管道

bool radioInit();
void open_listening();
bool radioRec(); //接收
void radioPair(); //配对函数
bool pairCheck(); //配对检查(检查标志位)

#endif
