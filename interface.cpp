#include"interface.h"

uint8_t sw_status[] = {NOT_PRESSED, NOT_PRESSED, NOT_PRESSED};
uint8_t pos = 2;
volatile uint8_t setled = 0;

void interface_init()
{
  pinMode(SW1, OUTPUT);
  digitalWrite(SW1, HIGH);
  pinMode(SW2, OUTPUT);
  digitalWrite(SW2, HIGH);
  pinMode(SW3, OUTPUT);
  digitalWrite(SW3, HIGH);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BZ, OUTPUT);
}

void Boot_Lantern(uint8_t c = 3) //开机动画
{
  for(uint8_t i = 0; i < c; i++)
  {
  PORTC = B00101010;
  delay(400);
  PORTC = B00010100;
  delay(400);
  }
  PORTC = B00000000;
}

void sw_press() //控制中键及配对状态下的左右键
{
  sw_status[MID] = keyDetect(SW1);

  if (current_STATUS == STATUS_PAIR) //非配对状态下禁用左右键
  {
    sw_status[LEFT] = keyDetect(SW2);
    sw_status[RIGHT] = keyDetect(SW3);

    if (sw_status[LEFT] == SHORT_PRESSED && rfStatus == RF_STATUS_START_PAIR) //配对确认状态下禁用左右键
    {
      if (setled % 2 == 1) //防止按下左右键改变ispair
      {
        ispair[pos] = !ispair[pos];
        setled = 0;
      }
      pos = (pos + 4) % 5;
    }
    if (sw_status[RIGHT] == 1 && rfStatus == RF_STATUS_START_PAIR)
    {
      if (setled % 2 == 1)
      {
        ispair[pos] = !ispair[pos];
        setled = 0;
      }
      pos = (pos + 1) % 5;
    }
  }

}

void Alarm() //控制标准状态下的led报警
{
  uint8_t i;
  for (i = 0; i < 5; i++)
  {
    digitalWrite(LED0 + i, alarm[i]);
  }
}

uint8_t led_set(bool ispair[]) //生成寄存器使用的二进制代码
{
  uint8_t i;
  uint8_t re = 0;

  for (i = 0; i < 5; i++)
  {
    if (ispair[i] == 0)
    {
      bitSet(re, i + 1);
    }
    else
    {
      bitClear(re, i + 1);
    }
  }
  return re;
}

void led_pair() //控制配对状态下的led闪烁
{
  if (current_STATUS == STATUS_PAIR)
  {
    PORTC = led_set(ispair);
    ispair[pos] = !ispair[pos];
    //PORTC = B00000000;
    setled++;
  }
}

void set_blink_rate(int f)
{
  blink_rate = f;
}

void BZ_alarm()
{
  tone(BZ, A6, 200);
}

void BZ_noneAlarm()
{
  /*
    tone(BZ, G4, 250);
    delay(200);
    tone(BZ, E4, 250);
    delay(200);
  */
  tone(BZ, C4, 250);
}
