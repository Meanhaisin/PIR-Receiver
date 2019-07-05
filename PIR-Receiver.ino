#include "Status.h"

//extern uint8_t setled;

void setup()
{
  Serial.begin(115200);
  system_init();
}

void loop()
{
  /*
    if (sw_status[MID] == SHORT_PRESSED)
    {
    Serial.println("MID SHORT_PRESSED");
    }
    if (sw_status[MID] == LONG_PRESSED)
    {
    Serial.println("MID LONG_PRESSED");
    }
    if (sw_status[LEFT] == SHORT_PRESSED)
    {
    Serial.println("LEFT SHORT_PRESSED");
    }
    if (sw_status[LEFT] == LONG_PRESSED)
    {
    Serial.println("LEFT LONG_PRESSED");
    }
    if (sw_status[RIGHT] == SHORT_PRESSED)
    {
    Serial.println("RIGHT SHORT_PRESSED");
    }
  */
  //Serial.println(keyDetect(SW1));

  switch (current_STATUS)
  {
    case STATUS_STD:
      DO_STATUS_std();
      break;

    case STATUS_MSG:
      DO_STATUS_msg();
      break;

    case STATUS_PAIR:
      DO_STATUS_pair();
      //Serial.println(setled);
      break;
  }

}
