#include "Status.h"

void setup() 
{
  //Serial.begin(115200);
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
  //Serial.println(digitalRead(SW3));
  /*
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
      break;
  }
  */
}
