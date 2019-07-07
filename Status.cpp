#include "Status.h"

volatile uint8_t current_STATUS = STATUS_STD;
bool alarm[] = {0, 0, 0, 0, 0};

void DO_STATUS_std()
{
  Alarm();
  //Serial.println("STATUS_STD");
  if (sw_status[MID] == LONG_PRESSED)
  {
    sw_status[MID] = NOT_PRESSED;
    current_STATUS = STATUS_PAIR;
    //rfStatus = RF_STATUS_START_PAIR;
    set_blink_rate(1000);
    //Boot_Lantern();
  }

  Powerdown(7200000);
}

void DO_STATUS_msg()
{
  //Serial.println("IRQ");
  radioRec();
  current_STATUS = STATUS_STD;
}

void DO_STATUS_pair()
{
  //Boot_Lantern();
  radioPair();
  //待加入按键逻辑
}
