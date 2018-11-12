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


uint8_t RFM95WLORAInitRegOpMode(uint8_t access_share_reg, uint8_t low_freq_mode_on, RFM95W_LORA_MODE mode)
{
  uint8_t reg = 0;
  uint16_t time_out_counter = 0;
  RFM95WLORASetMode(RFM95W_LORA_MODE_SLEEP);
  while(RFM95WLORAReadMode() != RFM95W_LORA_MODE_SLEEP && time_out_counter < 0xFFFF)
  {
    time_out_counter++;
  }
  if(time_out_counter == 0xFFFF)
  {
    return (uint8_t)-1;
  }

  time_out_counter = 0;
  RFM95WLORASetLoraFsk(RFM95W_LORA_LORA_MODE);
  // Maybe here should be some delay
  reg = (access_share_reg << 6) | (low_freq_mode_on << 3);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_OP_MODE, reg);
  RFM95WLORASetMode(mode);
  reg |= (uint8_t)mode;
  return reg;
}


RFM95W_LORA_MODE RFM95WLORAReadMode()
{
  RFM95W_LORA_MODE mode = RFM95W_LORA_MODE_SLEEP;
  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_OP_MODE);
  mode = (RFM95W_LORA_MODE)(reg & 0b111);
  return mode;
}


uint8_t RFM95WLORASetIrqFlagsMask(uint8_t mask)
{
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_IRQ_FLAGS_MASK, mask);
  return mask;
}


uint8_t RFM95WLORAReadIrqFlagsMask()
{
  return RFM95WLORAReadSingle(RFM95W_LORA_REG_IRQ_FLAGS_MASK);
}


uint8_t RFM95WLORAReadIrqFlags()
{
  return RFM95WLORAReadSingle(RFM95W_LORA_REG_IRQ_FLAGS);
}


uint8_t RFM95WLORAClearIrqFlags(uint8_t mask)
{
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_IRQ_FLAGS, mask);
  return mask;
}


uint8_t RFM95WLORAReadIrqFlag(RFM95W_LORA_IRQ_FLAG flag)
{
  uint8_t mask = RFM95WLORAReadSingle(RFM95W_LORA_REG_IRQ_FLAGS);
  mask &= flag;
  return (mask? 1: 0);
}


uint8_t RFM95WLORAClearIrqFlag(RFM95W_LORA_IRQ_FLAG flag)
{
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_IRQ_FLAGS, flag);
  return (uint8_t)flag;
}


uint8_t RFM95WLORASetFreq(uint32_t freq, uint32_t xosc_freq)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  float resolution = ((float)(1 << 19)) / ((float)xosc_freq);
  uint32_t reg_val = (uint32_t)(((float)freq) * resolution);
  uint8_t reg_buf[3] = {(uint8_t)(reg_val >> 16), (uint8_t)(reg_val >> 8), (uint8_t)(reg_val) };
  RFM95WLORAWriteBurst(RFM95W_LORA_REG_FRF_MSB, reg_buf, 3);
  return 0;
}

uint8_t RFM95WLORASetFreq868()
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  // 868000000/61.03515625 = 14221312
  uint32_t reg_val = 14221312;
  uint8_t reg_buf[3] = {(uint8_t)(reg_val >> 16), (uint8_t)(reg_val >> 8), (uint8_t)(reg_val) };
  RFM95WLORAWriteBurst(RFM95W_LORA_REG_FRF_MSB, reg_buf, 3);
  return 0;
}

uint8_t RFM95WLORASetPaConfig(uint8_t pa_select, uint8_t max_power, uint8_t output_power)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }
  pa_select &= 1;
  max_power &= 0b111;
  output_power &= 0b1111;

  uint8_t config = (pa_select << 7) | (max_power << 4) | (output_power);

  RFM95WLORAWriteSingle(RFM95W_LORA_REG_PA_CONFIG, config);

  return 0;
}

uint8_t RFM95WLORASetPaSelect(uint8_t pa_select)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }
  pa_select &= 1;

  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_PA_CONFIG);
  reg &= 0b01111111;
  reg |= (pa_select << 7);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_PA_CONFIG, reg);
  return 0;
}

uint8_t RFM95WLORASetPaMaxPower(uint8_t max_power)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }
  max_power &= 0b111;

  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_PA_CONFIG);
  reg &= 0b10001111;
  reg |= (max_power << 4);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_PA_CONFIG, reg);
  return 0;
}


uint8_t RFM95WLORASetOcpConfig(uint8_t osp_on, uint8_t ocp_trim)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }
  osp_on &= 1;
  ocp_trim &= 0b11111;

  uint8_t config = (osp_on << 5) | (ocp_trim);

  RFM95WLORAWriteSingle(RFM95W_LORA_REG_OCP, config);

  return 0;
}


uint8_t RFM95WLORASetOcpOn(uint8_t osp_on)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }
  osp_on &= 1;

  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_OCP);
  reg &= 0b11011111;
  reg |= (osp_on << 5);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_OCP, reg);

  return 0;
}

uint8_t RFM95WLORASetOcpTrim(uint8_t osp_trim)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }
  osp_trim &= 1;

  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_OCP);
  reg &= 0b11100000;
  reg |= (osp_trim);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_OCP, reg);

  return 0;
}
