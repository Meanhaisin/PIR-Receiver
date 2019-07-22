#include "key.h"

/* 按键扫描程序所处的状态
  初始状态为：按键按下（KEY_STATE_RELEASE）
*/
uint8_t keyState[] = {0, 0, 0, 0, 0, 0, 0, 0}; // 组合键(左+右)，保留，中键，保留，左键，保留，保留，右键

uint8_t keyDetect(uint8_t sw)
{
  static unsigned int duriation[] = {0, 0, 0, 0, 0, 0, 0, 0}; // 用于在等待状态中计数

  switch (sw)
  {
    case COMBINATION:
      switch (keyState[sw])
      {
        case KEY_STATE_RELEASE:
          if (!(digitalRead(SW2) || digitalRead(SW3)))
          {
            keyState[sw] = KEY_STATE_WAITING;
          }
          else
          {
            return NOT_PRESSED;
          }
          break;

        case KEY_STATE_WAITING:
          if (digitalRead(SW2) && digitalRead(SW3))
          {
            keyState[sw] = KEY_STATE_RELEASE;
            return COMBINED;
          }
          break;
      }
      break;

    default:
      switch (keyState[sw])
      {
        case KEY_STATE_RELEASE:
          if (digitalRead(sw) == 0)    // 如果按键按下
          {
            keyState[sw] = KEY_STATE_SHORT_PRESSED;  // 转换至下一个状态
          }
          return NOT_PRESSED;    // 返回：按键未按下
          break;

        case KEY_STATE_SHORT_PRESSED:
          if (digitalRead(sw) == 0)
          {
            duriation[sw]++;

            if (duriation[sw] > LONG_PRESSED_TIME)   // 如果经过多次检测，按键仍然按下
            {
              duriation[sw] = 0;
              keyState[sw] = KEY_STATE_LONG_PRESSED;  // 转换至下一个状态
            }
            return NOT_PRESSED;
          }
          else
          {
            duriation[sw] = 0;
            keyState[sw] = KEY_STATE_RELEASE;
            return SHORT_PRESSED;
          }
          break;

        case KEY_STATE_LONG_PRESSED:
          if (digitalRead(sw) == 1)      // 如果按键松开
          {
            keyState[sw] = KEY_STATE_RELEASE;  // 回到按键松开的状态
            return LONG_PRESSED;
          }
          else
          {
            return NOT_PRESSED;
          }
          break;
      }
      break;
  }
}
