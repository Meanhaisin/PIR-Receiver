#include "Status.h"

volatile uint8_t current_STATUS = STATUS_STD;
bool alarm[] = {0, 0, 0, 0, 0};

void DO_STATUS_std()
{
  Alarm();

  if(sw_status[MID] == LONG_PRESSED)
  {
    current_STATUS = STATUS_PAIR;
  }
}

void DO_STATUS_msg()
{
  radioRec();
  current_STATUS = STATUS_STD;
}

void DO_STATUS_pair()
{
  //Boot_Lantern();
  radioPair();

  //待加入按键逻辑
}
