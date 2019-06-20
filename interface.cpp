#include"interface.h"

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

void Boot_Lantern()
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
  
}
