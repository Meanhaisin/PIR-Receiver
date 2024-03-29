#ifndef _key_H
#define _key_H

#include <Arduino.h>
#include "interface.h"

/* 按键状态机中的三个状态 */
#define KEY_STATE_RELEASE   0 // 按键未按下
#define KEY_STATE_WAITING   1 // 等待
#define KEY_STATE_SHORT_PRESSED   2 // 按键按下（等待释放）
#define KEY_STATE_LONG_PRESSED   3

/*等待状态持续时间
  需要根据单片机速度和按键消抖程序被调用的速度来进行调整
*/
#define LONG_PRESSED_TIME 400
//#define COMBINATION_DELAY 20

#define COMBINED 3
#define LONG_PRESSED 2
#define SHORT_PRESSED 1
#define NOT_PRESSED 0

uint8_t keyDetect(uint8_t sw);

#endif
