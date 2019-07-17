#include "system.h"

bool ledchange = 1;
bool ledflag = 0;
unsigned int blink_rate = 1000;

void system_init() //初始化端口、RF模块、检测设备是否完成配对（未配对进入STATUS_pair,否则进入STATUS_std)
{
  pinMode(IRQ, INPUT);

  interface_init();

  Boot_Lantern(1);

  if (radioInit())
  {
    current_STATUS = STATUS_STD;
  }
  else
  {
    current_STATUS = STATUS_PAIR;
    rfStatus = RF_STATUS_START_PAIR;
  }

  Timer1.initialize(INTERVAL);
  Timer1.attachInterrupt(time_isr);
  attachInterrupt(digitalPinToInterrupt(IRQ), rec_isr, FALLING);
}

uint8_t bat_voltage()
{
  return analogRead(BAT) / 8;
}

uint8_t BatPercent()
{
  return map(analogRead(BAT), 368, 615, 0, 100); //1V8-3V
}

void rec_isr()
{
  current_STATUS = STATUS_MSG;
}

void time_isr()
{
  static long isr_timer = 0;
  isr_timer++;
  if (isr_timer % 1 == 0) //便于调时
  {
    sw_press();
  }
  
  if (isr_timer % blink_rate == 0)
  {
    led_pair();
  }
}

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

void Powerdown(unsigned long m,uint8_t p)
{
  if (millis() > m or BatPercent() < p)
  {
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  }
}
