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

  if (sw_status[LEFT] == LONG_PRESSED)
  {
    sw_status[LEFT] = NOT_PRESSED;
    
    mute = !mute;
    writeConfig(CONFIG0, configGEN(mute));
    
    tone(BZ, G4, 50);
  }

  PowerSave(POWERDOWN_T, 20);
}

void DO_STATUS_msg()
{
  noSleep();
  if (millis() - power_t > POWERDOWN_T)
  {
    power_t = millis() + POWERDOWN_T - WAKEUP_T_IRQ;
  }
  
  radioRec();
  
  current_STATUS = STATUS_STD;
}

void DO_STATUS_pair()
{
  radioPair();
}
