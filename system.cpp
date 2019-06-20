#include "system.h"

bool ledchange = 1;
bool ledflag = 0;

bool system_init() //初始化端口、RF模块、检测设备是否完成配对（未配对进入STATUS_pair,否则进入STATUS_std)
{
  pinMode(IRQ, INPUT);

  interface_init();

  Boot_Lantern();

  if (!radioInit())
  {
    return 0;
  }
  else
  {
    return 1;
  }

  attachInterrupt(IRQ - 1, isr, FALLING);
}

uint8_t bat_voltage()
{

  return analogRead(BAT) / 8;

}

void isr()
{
  current_STATUS = STATUS_MSG;
}

/*
  void led_blink()
  {

  if (ledchange == 1) //开始配对
  {
    static uint8_t duriation;
    if(ledflag == 1 && duriation < LED_DELAY_SLOW) //led high
    {
      digitalWrite(LED, HIGH);
      duriation++;
    }
    else if(ledflag == 0 && duriation < LED_DELAY_SLOW) //led low
    {
      digitalWrite(LED, LOW);
      duriation++;
    }
    else  //time change
    {
      duriation = 0;
      ledflag = !ledflag;
    }
  }

  }
*/
/*
  void blink_block(uint8_t t, uint8_t count)
  {

  for (uint8_t i = 0; i < t; i++)
  {
    digitalWrite(LED, HIGH);
    delay(t);
    digitalWrite(LED, LOW);
    delay(t);
  }

  }
*/
