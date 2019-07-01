#include "Status.h"
extern uint8_t setled;
void setup() 
{
  Serial.begin(115200);
  if(system_init())
  {
    current_STATUS = STATUS_STD;
  }
  else
  {
    current_STATUS = STATUS_PAIR;
    rfStatus = RF_STATUS_START_PAIR;
  }
  interface_init();
}
  
void loop() 
{
  if (sw_status[MID] == SHORT_PRESSED) Serial.println(SHORT_PRESSED);
  
  /*
  if(sw_status[SW1] != 0)
  {
    Serial.println(sw_status[MID]);
  }
  */
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
