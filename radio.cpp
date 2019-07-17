#include "radio.h"
//#include "printf.h"

byte rec_pipe[5][5]; //接收管道,从EEPROM读取
uint8_t rfStatus = RF_STATUS_START_PAIR;
bool ispair[5] = {0}; //是否已配对

RF24 RF(CE, CSN);

bool radioInit()
{
  RF.begin();
  RF.setDataRate(RF24_250KBPS); //发射速率设定,最小速率以增大距离
  RF.setPALevel(RF24_PA_HIGH); //发射功率设定,测试后可适当调小以节能
  RF.setPayloadSize(PAY_LOAD_SIZE_STD); //发射负载大小(Byte)
  RF.maskIRQ(1, 1, 0); //(tx_ok,tx_fail,rx_ready) 设置中断类型,屏蔽发送、发送失败中断,保留接收中断
  if (pairCheck())
  {
    open_listening();
    return 1;
  }
  else
  {
    return 0;
  }
}

void open_listening()
{
  readPipe();
  for (uint8_t i = 0; i < PIPE_NUM_MAX; i++)
  {
    RF.openReadingPipe(REC_READINGPIPE_OFFSITE + i, rec_pipe[i]);
  }
  RF.startListening();
/*
  for (int i = 0; i < 5; i++)
  {
    for (int t = 0; t < 5; t++)
    {
      Serial.print(rec_pipe[i][t]);
    }
    Serial.println("");
  }
*/
/*
  printf_begin();
  //输出测试
  RF.printDetails();
*/
}

bool radioRec()
{
  uint8_t msg = 0;
  uint8_t pipeNum = 0;

  RF.available(&pipeNum);
  RF.read(&msg, sizeof(msg));
  //Serial.println(msg);

  if (msg % 2 == 1)
  {
    alarm[pipeNum - 1] = 1;
    BZ_alarm();
    return 1;
  }
  else
  {
    alarm[pipeNum -1 ] = 0;
    BZ_noneAlarm();
    return 0;
  }
}

void radioPair()
{
  static byte tmp_pipe[5];

  switch (rfStatus)
  {
    case RF_STATUS_START_PAIR:
      detachInterrupt(digitalPinToInterrupt(IRQ));

      RF.stopListening();
      RF.setPayloadSize(PAY_LOAD_SIZE_PAIR);
      RF.openWritingPipe(pair_pipe);
      //Boot_Lantern();

      if (sw_status[MID] == SHORT_PRESSED)
      {
        rfStatus = RF_STATUS_PAIRING;
        readSN(tmp_pipe);
        tmp_pipe[0] = pos;
        set_blink_rate(500);
        //Boot_Lantern();
      }
      else if (sw_status[MID] == LONG_PRESSED)
      {
        //sw_status[MID] = NOT_PRESSED;
        current_STATUS = STATUS_STD;

        RF.setPayloadSize(PAY_LOAD_SIZE_STD);
        open_listening();

        attachInterrupt(digitalPinToInterrupt(IRQ), rec_isr, FALLING);
      }
      break;

    case RF_STATUS_PAIRING:
      if (RF.write(&tmp_pipe, sizeof(tmp_pipe)))
      {
        ispair[pos] = 1;
        writeNO(pos, tmp_pipe);

        rfStatus = RF_STATUS_START_PAIR;
        current_STATUS = STATUS_STD;

        RF.setPayloadSize(PAY_LOAD_SIZE_STD);
        open_listening();

        attachInterrupt(digitalPinToInterrupt(IRQ), rec_isr, FALLING);

        blink_block(pos + LED0, 100, 3);
      }
      break;
  }
}

/*
  void radioSend(bool flag)
  {
  uint8_t msg = 0;

  if (flag)
  {
    msg = bat_voltage() * 2 + 1;
  }
  else
  {
    msg = bat_voltage() * 2;
  }

  RF.write(&msg, sizeof(msg));
  }
*/
/*
  void radioPair()
  {

  switch (rfStatus)
  {
    case RF_STATUS_START_PAIR:
      RF.openReadingPipe(PAIR_READINGPIPE, pair_pipe);
      RF.startListening();
      rfStatus = RF_STATUS_PAIRING;
      break;

    case RF_STATUS_PAIRING:
      if (RF.available())
      {
        //ledchange = 1;
        RF.read(&send_pipe, sizeof(send_pipe));
        writePipe(send_pipe);
        RF.stopListening();
        RF.closeReadingPipe(PAIR_READINGPIPE);
        //        blink_block(10,3);
        rfStatus = RF_STATUS_STD;
        current_STATUS = STATUS_STD;
      }

        else
        {
        ledchange = 0;
        }

      break;
  }
  }
*/
bool pairCheck()
{
  bool flag = 0;

  for (uint8_t i = 0 ; i < 5 ; i++)
  {
    if (EEPROM.read(NO_OFFSITE + i) == NONE)
    {
      ispair[i] = 0;
    }
    else
    {
      ispair[i] = 1;
    }
  }

  for (uint8_t i = 0 ; i < 5 ; i++)
  {
    if (ispair[i] == 1)
    {
      flag = 1;
      break;
    }
  }

  return flag;
}
