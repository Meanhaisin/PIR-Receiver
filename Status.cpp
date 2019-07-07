#include "Status.h"

volatile uint8_t current_STATUS = STATUS_STD;
bool alarm[] = {0, 0, 0, 0, 0};

void DO_STATUS_std()
{
  Alarm();
  if (sw_status[MID] == LONG_PRESSED)
  {
    sw_status[MID] = NOT_PRESSED;
    current_STATUS = STATUS_PAIR;
    set_blink_rate(1000);
  }

  Powerdown(7200000,3);
}

void DO_STATUS_msg()
{
  radioRec();
  current_STATUS = STATUS_STD;
}

void DO_STATUS_pair()
{
  radioPair();
}
