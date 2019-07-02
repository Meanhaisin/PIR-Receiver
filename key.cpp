#include "key.h"

//bool keyflag = 0;

/* 按键扫描程序所处的状态
  初始状态为：按键按下（KEY_STATE_RELEASE）
*/

uint8_t keyState = KEY_STATE_RELEASE;

/*
bool readKey(int sw)
{
  //Boot_Lantern();
  if (digitalRead(sw))
  {
    //Boot_Lantern();
    return 0;
  }
  else
  {
    //Boot_Lantern();
    return 1;
  }
}
*/
/*
uint8_t de_bug()
{
  static uint8_t debug = 0;
  if (readKey(SW2) != keyflag)
  {
    keyflag = readKey(SW2);
    debug++;
  }
  return debug;
}
*/
/*
  uint8_t keyDetect(int sw)
  {
  volatile static uint8_t duriation;  // 用于在等待状态中计数

  switch (keyState)
  {
    case KEY_STATE_RELEASE:
      if (readKey(sw) == 1)    // 如果按键按下
      {
        keyState = KEY_STATE_WAITING;  // 转换至下一个状态
        //Boot_Lantern();
      }
      return NOT_PRESSED;    // 返回：按键未按下
      break;

    case KEY_STATE_WAITING:
      if (readKey(sw) == 1)    // 如果按键按下
      {
        duriation++;
        //Boot_Lantern();
        if (duriation >= PRESSED_TIME)   // 如果经过多次检测，按键仍然按下
        { // 说明没有抖动了，可以确定按键已按下
          duriation = 0;
          keyState = KEY_STATE_SHORT_PRESSED;  // 转换至下一个状态
        }
      }
      else  // 如果此时按键松开
      { // 可能存在抖动或干扰
        duriation = 0;  // 清零的目的是便于下次重新计数
        keyState = KEY_STATE_RELEASE;  // 重新返回按键松开的状态
        return NOT_PRESSED;
      }
      break;

    case KEY_STATE_SHORT_PRESSED:
      if (readKey(sw) == 1)
      {
        duriation++;
        if (duriation >= LONG_PRESSED_TIME)   // 如果经过多次检测，按键仍然按下
        {
          duriation = 0;
          keyState = KEY_STATE_LONG_PRESSED;  // 转换至下一个状态
          //return LONGT_PRESSED;
        }
      }
      else
      {
        duriation = 0;
        keyState = KEY_STATE_RELEASE  ;
        return SHORT_PRESSED;
      }
      break;


    case KEY_STATE_LONG_PRESSED:
      if (readKey(sw) == 0)      // 如果按键松开
      {
        keyState = KEY_STATE_RELEASE;  // 回到按键松开的状态
        return LONG_PRESSED;
      }
      break;

    default:
      keyState = KEY_STATE_RELEASE;
      return NOT_PRESSED;
      break;
  }
  }
*/
uint8_t keyDetect(int sw)
{
  //static uint8_t duriation = 1;  // 用于在等待状态中计数
  //Serial.println(duriation);

  switch (keyState)
  {
    /*
    case KEY_STATE_RELEASE:
      if (digitalRead(sw) == 0)    // 如果按键按下
      {
        keyState = KEY_STATE_SHORT_PRESSED;  // 转换至下一个状态
        //Boot_Lantern();
      }
      return NOT_PRESSED;    // 返回：按键未按下
      break;
      */

    case KEY_STATE_SHORT_PRESSED:
      static uint8_t duriation = 0;
      //Serial.println(duriation);
      //if(duriation % 3 == 0)
      
      if (digitalRead(sw) == 0)
      {
        duriation++;
        
        //Serial.println(duriation);
        //Boot_Lantern();
        if (duriation >= LONG_PRESSED_TIME)   // 如果经过多次检测，按键仍然按下
        {
          duriation = 0;
          //Boot_Lantern();
          keyState = KEY_STATE_LONG_PRESSED;  // 转换至下一个状态
          //return LONGT_PRESSED;
        }
      }
      else
      {
       // Serial.println(readKey(sw));
        duriation = 0;
        keyState = KEY_STATE_RELEASE  ;
        return SHORT_PRESSED;
      }
      
      break;

    case KEY_STATE_LONG_PRESSED:
      if (digitalRead(sw) == 1)      // 如果按键松开
      {
        keyState = KEY_STATE_SHORT_PRESSED;  // 回到按键松开的状态
        return LONG_PRESSED;
      }
      break;

    default:
      keyState = KEY_STATE_SHORT_PRESSED;
      return NOT_PRESSED;
      break;
  }
}
