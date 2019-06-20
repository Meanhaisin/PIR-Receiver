#include "ROM.h"

void writePipe(byte pipe[])
{
  for (uint8_t i = PIPE_OFFSITE; i < SN_WIDTH; i++)
  {
    EEPROM.update(i, pipe[i]);
  }
}

void writeNO(uint8_t no ,byte pipe[])
{
  EEPROM.update(PIPE_WIDTH + no, pipe[0]);
}

void readPipe()
{
  for (uint8_t t = 0; t < PIPE_NUM_MAX; t++)
  {
    for (uint8_t i = PIPE_OFFSITE; i < SN_WIDTH; i ++)
    {
      rec_pipe[t][SN_WIDTH - i] = EEPROM.read(i);
    }
  }

  for (uint8_t i = NO_OFFSITE; i < PIPE_NUM_MAX; i++)
  {
    rec_pipe[0][i] = EEPROM.read(i);
  }
}

void delPipe(uint8_t no)
{
  EEPROM.update(NO_OFFSITE + no, 0);
}

void readSN(byte * sn)
{
  for (int i = SN_OFFSITE; i < SN_WIDTH; i++)
  {
//    rec_pipe[SN_WIDTH - i] = EEPROM.read(i);
  }
}
