#include "Status.h"

void setup()
{
  system_init();
}

void loop()
{ 
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
}
