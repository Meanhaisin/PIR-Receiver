#ifndef _ROM_H
#define _ROM_H

#include <Arduino.h>
#include <EEPROM.h>
#include "radio.h"

#define PIPE_WIDTH 5
#define PIPE_OFFSITE 0
#define NO_OFFSITE 4
#define PIPE_NUM_MAX 5 
#define SN_WIDTH 4
#define SN_OFFSITE 1020
#define NONE 0xFF
#define CONFIG0 1019

extern byte rec_pipe[5][5];

void writePipe(const byte pipe[]); //写入管道
void writeNO(uint8_t no ,const byte pipe[]); //设置标志位(管道第一位)
void readPipe();
void delPipe(uint8_t no); //删除管道(只需清除标志位)
void readSN(byte sn[]);
void writeConfig(unsigned int addr,uint8_t config);
uint8_t readConfig(unsigned int addr);

#endif
