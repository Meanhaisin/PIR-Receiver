#include "ROM.h"

void writePipe(byte pipe[])
{
  for (uint8_t i = PIPE_OFFSITE; i < PIPE_WIDTH; i++)
  {
    EEPROM.update(i, pipe[i]);
  }
}

void readPipe()
{
  for (uint8_t i = PIPE_OFFSITE; i < PIPE_WIDTH; i++)
  {
    send_pipe[i] = EEPROM.read(i);
  }
}

void delPipe()
{
  EEPROM.update(NO_OFFSITE,0);
}
