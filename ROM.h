#ifndef _ROM_H
#define _ROM_H

#include "Arduino.h"
#include "EEPROM.h"
#include "radio.h"

extern byte send_pipe[5];

#define PIPE_WIDTH 5
#define PIPE_OFFSITE 0
#define NO_OFFSITE 5
#define SN_OFFSITE 1000

void writePipe(byte pipe[]); //写入管道,同时设置标志位
void readPipe();
void delPipe(); //删除管道(只需清除标志位)

#endif
