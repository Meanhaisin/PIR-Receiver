#include "ROM.h"

void writePipe(const byte pipe[])
{
  for (uint8_t i = PIPE_OFFSITE; i < SN_WIDTH; i++)
  {
    EEPROM.update(i, pipe[i + 1]);
  }
}

void writeNO(uint8_t no ,const byte pipe[])
{
  EEPROM.update(NO_OFFSITE + no, pipe[0]);
}

void readPipe()
{
  for (uint8_t t = 0; t < PIPE_NUM_MAX; t++)
  {
    for (uint8_t i = PIPE_OFFSITE; i < SN_WIDTH; i ++)
    {
      rec_pipe[t][i + 1] = EEPROM.read(i);
    }
  }

  for (uint8_t i = 0; i < PIPE_NUM_MAX; i++)
  {
    rec_pipe[i][0] = EEPROM.read(i + NO_OFFSITE);
  }
}

void delPipe(uint8_t no)
{
  EEPROM.update(NO_OFFSITE + no, NONE);
}

void readSN(byte sn[])
{
  for (int i = 0; i < SN_WIDTH; i++)
  {
    sn[i + 1] = EEPROM.read(i + SN_OFFSITE);
  }
}
