#include "system.h"

bool ledchange = 1;
bool ledflag = 0;
long long isr_t;

bool system_init() //初始化端口、RF模块、检测设备是否完成配对（未配对进入STATUS_pair,否则进入STATUS_std)
{
  pinMode(IRQ, INPUT);

  interface_init();

  Timer1.initialize(INTERVAL);
  Timer1.attachInterrupt(time_isr);
  attachInterrupt(IRQ - 1, isr, FALLING);

  if (!radioInit())
  {
    return 0;
  }
  else
  {
    return 1;
  }

  
}

uint8_t bat_voltage()
{

  return analogRead(BAT) / 8;

}

void isr()
{
  current_STATUS = STATUS_MSG;
}

void time_isr()
{
  static long long isr_timer = 0;
  //Boot_Lantern();
  isr_timer++;
  isr_t = isr_timer;
  if(isr_timer % 1 == 0) //便于调时
  {
    //Boot_Lantern();
    sw_press();
    //Boot_Lantern();
  }
  if(isr_timer % 500 == 0)
  {
    led_pair();
    //isr_timer = 0;
    //Boot_Lantern();
  }
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

void blink_block(uint8_t pin, uint8_t t, uint8_t count)
{

  for (uint8_t i = 0; i < count; i++)
  {
    digitalWrite(pin, HIGH);
    delay(t);
    digitalWrite(pin, LOW);
    delay(t);
  }

}
