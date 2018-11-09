#include "RFM95W_driver.h"

uint8_t RFM95WLORASetMode(RFM95W_LORA_MODE mode)
{
  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_OP_MODE);
  reg &= 0b11111000;
  reg |= mode;
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_OP_MODE, reg);
  return reg;
}

uint8_t RFM95WLORASetLoraFsk(uint8_t global_mode)
{
  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_OP_MODE);
  if((reg & 0b11) != RFM95W_LORA_MODE_SLEEP)
  {
    // Module must be in sleep mode to switch module
    return (uint8_t)-1;
  }
  reg &= 0b1111111;
  reg |= ((global_mode&0b1) << 7);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_OP_MODE, reg);
  return reg;
}

uint8_t RFM95WLORASetFreqMode(uint8_t freq_mode)
{
  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_OP_MODE);
  reg &= 0b11110111;
  reg |= ((freq_mode&0b1) << 3);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_OP_MODE, reg);
  return reg;
}
