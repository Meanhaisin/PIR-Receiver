#include"interface.h"
extern bool alarm[];
uint8_t sw_status[] = {0,0,0};
uint8_t pos = 2;

void interface_init()
{
  pinMode(SW1,OUTPUT);
  digitalWrite(SW1,HIGH);
  pinMode(SW2,OUTPUT);
  digitalWrite(SW2,HIGH);
  pinMode(SW3,OUTPUT);
  digitalWrite(SW3,HIGH);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(BZ,OUTPUT);
}

void Boot_Lantern() //开机动画
{
  PORTC = B00101010;
  delay(400);
  PORTC = B00010100;
  delay(400);
  PORTC = B00101010;
  delay(400);
  PORTC = B00010100;
  delay(400);
  PORTC = B00101010;
  delay(400);
  PORTC = B00010100;
  delay(400);
  PORTC = B00000000;
}

void sw_press()
{
  sw_status[MID] = keyDetect(SW1);
  sw_status[LEFT] = keyDetect(SW2);
  sw_status[RIGHT] = keyDetect(SW3);

  if(sw_status[LEFT] == 1)
  {
    pos = (pos + 4) % 5;
  }
  if(sw_status[RIGHT] == 1)
  {
    pos = (pos + 1) % 5;
  }
}

void Alarm()
{
  uint8_t i;
  for(i=0;i<5;i++)
  {
    digitalWrite(LED1 + i,alarm[i]);
  }
}
