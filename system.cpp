#include "system.h"

unsigned int blink_rate = 1000;
bool mute = false;

void system_init() //初始化端口、RF模块、检测设备是否完成配对（未配对进入STATUS_pair,否则进入STATUS_std)
{
  pinMode(IRQ, INPUT);
  disablePower(POWER_SERIAL0); // 关闭串口  

  interface_init();

  Boot_Lantern(1);

  setConfig();

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
  return analogRead(BAT) << 1;
}

uint8_t BatPercent()
{
  unsigned int b = analogRead(BAT);
  
  if(b > 368)
  {
  return map(b, 368, 615, 0, 100); //1V8-3V
  }
  else
  {
    return 0;
  }
}

void rec_isr()
{
  if (digitalRead(IRQ) == LOW)
  {
    current_STATUS = STATUS_MSG;
  }
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

void PowerSave(unsigned long m, uint8_t p)
{
  if (millis() > m || BatPercent() < p)
  {
    sleepMode(SLEEP_POWER_DOWN); //约节省电流26mA
    sleep();
  }
}

void setConfig()
{
  uint8_t config = readConfig(CONFIG0);

  mute = bitRead(config,0);
}

uint8_t configGEN(bool f)
{
  uint8_t c = 0;

  if(f)
  {
  bitSet(c,0);
  }
  return c;
}
