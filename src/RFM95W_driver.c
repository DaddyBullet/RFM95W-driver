#include "RFM95W_driver.h"

uint8_t RFM95WLORAReadVersion()
{
  return RFM95WLORAReadSingle(RFM95W_LORA_REG_VERSION);
}

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
  reg = (1 << 7) | (access_share_reg << 6) | (low_freq_mode_on << 3); //Since we put device into LORA_Mode
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


uint8_t RFM95WLORASetDIO(RFM95W_LORA_DIO_TYPE dio, uint8_t func)
{
  if(func > 2)
  {
    return (uint8_t)-1;
  }
  uint8_t reg_val = 0;
  switch (dio)
  {
    case RFM95W_LORA_DIO0:
    {
      reg_val = RFM95WLORAReadSingle(RFM95W_LORA_REG_DIO_MAPPING1);
      reg_val &= ~0xC0;
      reg_val |= (func << 6);
      RFM95WLORAWriteSingle(RFM95W_LORA_REG_DIO_MAPPING1, reg_val);
      break;
    }
    case RFM95W_LORA_DIO1:
    {
      reg_val = RFM95WLORAReadSingle(RFM95W_LORA_REG_DIO_MAPPING1);
      reg_val &= ~0x30;
      reg_val |= (func << 4);
      RFM95WLORAWriteSingle(RFM95W_LORA_REG_DIO_MAPPING1, reg_val);
      break;
    }
    case RFM95W_LORA_DIO2:
    {
      reg_val = RFM95WLORAReadSingle(RFM95W_LORA_REG_DIO_MAPPING1);
      reg_val &= ~0x0C;
      reg_val |= (func << 2);
      RFM95WLORAWriteSingle(RFM95W_LORA_REG_DIO_MAPPING1, reg_val);
      break;
    }
    case RFM95W_LORA_DIO3:
    {
      reg_val = RFM95WLORAReadSingle(RFM95W_LORA_REG_DIO_MAPPING1);
      reg_val &= ~0x03;
      reg_val |= (func << 0);
      RFM95WLORAWriteSingle(RFM95W_LORA_REG_DIO_MAPPING1, reg_val);
      break;
    }
    case RFM95W_LORA_DIO4:
    {
      reg_val = RFM95WLORAReadSingle(RFM95W_LORA_REG_DIO_MAPPING2);
      reg_val &= ~0xC0;
      reg_val |= (func << 6);
      RFM95WLORAWriteSingle(RFM95W_LORA_REG_DIO_MAPPING2, reg_val);
      break;
    }
    case RFM95W_LORA_DIO5:
    {
      reg_val = RFM95WLORAReadSingle(RFM95W_LORA_REG_DIO_MAPPING2);
      reg_val &= ~0x30;
      reg_val |= (func << 4);
      RFM95WLORAWriteSingle(RFM95W_LORA_REG_DIO_MAPPING2, reg_val);
      break;
    }
    default:
    {
      break;
    }
  }
  return 0;
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
  RFM95WLORAWriteBurst(RFM95W_LORA_REG_FR_MSB, reg_buf, 3);
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
  RFM95WLORAWriteBurst(RFM95W_LORA_REG_FR_MSB, reg_buf, 3);
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


uint8_t RFM95WLORASetLnaConfig(uint8_t lna_gain, uint8_t lna_boost_lf, uint8_t lna_boost_hf)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }
  lna_gain &= 0b111;
  lna_boost_lf &= 0b11;
  lna_boost_hf &= 0b11;

  uint8_t config = (lna_gain << 5) | (lna_boost_lf << 3) | (lna_boost_hf);

  RFM95WLORAWriteSingle(RFM95W_LORA_REG_LNA, config);

  return 0;
}


uint8_t RFM95WLORASetLnaGain(uint8_t lna_gain)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }
  lna_gain &= 0b111;

  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_LNA);
  reg &= 0b00011111;
  reg |= (lna_gain << 5);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_LNA, reg);

  return 0;
}

uint8_t RFM95WLORASetLnaBoostLf(uint8_t lna_boost_lf)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }
  lna_boost_lf &= 0b11;

  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_LNA);
  reg &= 0b11100111;
  reg |= (lna_boost_lf << 3);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_LNA, reg);

  return 0;
}

uint8_t RFM95WLORASetLnaBoostHf(uint8_t lna_boost_hf)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }
  lna_boost_hf &= 0b11;

  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_LNA);
  reg &= 0b11111100;
  reg |= (lna_boost_hf);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_LNA, reg);

  return 0;
}

uint8_t RFM95WLORASetModemConfig(RFM95W_LORA_BANDWIDTH bw, RFM95W_LORA_CR cr, RFM95W_LORA_SF sf, \
                              RFM95W_LORA_HEADER_MODE hm, \
                              RFM95W_LORA_TX_MODE tx_mode, \
                              RFM95W_LORA_RX_PAYLOAD_CRC rx_crc)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  uint8_t reg_1 = ((uint8_t)bw << 4) | ((uint8_t)cr << 1) | ((uint8_t)hm);
  uint8_t reg_2 = RFM95WLORAReadSingle(RFM95W_LORA_REG_MODEM_CONFIG_2);
  reg_2 &= 0b00000011;
  reg_2 |= ((uint8_t)sf << 4) | ((uint8_t)tx_mode << 3) | ((uint8_t)rx_crc << 2);

  RFM95WLORAWriteSingle(RFM95W_LORA_REG_MODEM_CONFIG, reg_1);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_MODEM_CONFIG_2, reg_2);
  return 0;
}

uint8_t RFM95WLORASetModemConfigFull(RFM95W_LORA_BANDWIDTH bw, RFM95W_LORA_CR cr, RFM95W_LORA_SF sf, \
                              RFM95W_LORA_HEADER_MODE hm, \
                              RFM95W_LORA_TX_MODE tx_mode, \
                              RFM95W_LORA_RX_PAYLOAD_CRC rx_crc, \
                              RFM95W_LORA_NODE node, \
                              RFM95W_LORA_AGC_AUTO agc)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  RFM95WLORASetModemConfig(bw, cr, sf, hm, tx_mode, rx_crc);

  uint8_t reg_3 = RFM95WLORAReadSingle(RFM95W_LORA_REG_MODEM_CONFIG_3);
  reg_3 &= 0b11110011;
  reg_3 |= ((uint8_t)node << 3) | ((uint8_t)agc << 2);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_MODEM_CONFIG_3, reg_3);

  return 0;
}

uint8_t RFM95WLORASetBandwidth(RFM95W_LORA_BANDWIDTH bw)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_MODEM_CONFIG);
  reg &= 0b00001111;
  reg |= ((uint8_t)bw << 4);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_MODEM_CONFIG, reg);

  return 0;
}

uint8_t RFM95WLORASetCodingRate(RFM95W_LORA_CR cr)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_MODEM_CONFIG);
  reg &= 0b11110001;
  reg |= ((uint8_t)cr << 1);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_MODEM_CONFIG, reg);

  return 0;
}

uint8_t RFM95WLORASetSpreadingFactor(RFM95W_LORA_SF sf)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  uint8_t reg = RFM95WLORAReadSingle(RFM95W_LORA_REG_MODEM_CONFIG_2);
  reg &= 0b00001111;
  reg |= ((uint8_t)sf << 4);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_MODEM_CONFIG_2, reg);

  return 0;
}

uint8_t RFM95WLORASetHopPeriod(uint8_t hop_period)
{
  return RFM95WLORAWriteSingle(RFM95WLORA_REG_HOP_PERIOD, hop_period);
}

uint8_t RFM95WLORAReadFhssPresentChannel()
{
  return RFM95WLORAReadSingle(RFM95WLORA_REG_HOP_CHANNEL) & 0b111111;
}


int16_t RFM95WLORAReadRssi()
{
  return ((int16_t)RFM95WLORAReadSingle(RFM95W_LORA_REG_RSSI_VALUE)) - 137;
}

int16_t RFM95WLORAReadPacketRssi()
{
  return ((int16_t)RFM95WLORAReadSingle(RFM95W_LORA_REG_PKT_RSSI_VALUE)) - 137;
}

int8_t RFM95WLORAReadPacketSnr()
{
  return ((int8_t)RFM95WLORAReadSingle(RFM95W_LORA_REG_PKT_SNR_VALUE))/4;
}


uint8_t RFM95WLORASetSymbTimeout(uint16_t symb_timeout)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  symb_timeout &= 0b1111111111;

  uint8_t reg_1 = RFM95WLORAReadSingle(RFM95W_LORA_REG_MODEM_CONFIG_2);
  reg_1 &= 0b11111100;
  reg_1 |= (uint8_t)(symb_timeout >> 8);
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_MODEM_CONFIG_2, reg_1);

  uint8_t reg_2 = (uint8_t)symb_timeout;
  RFM95WLORAWriteSingle(RFM95W_LORA_REG_SYMB_TIMEOUT_LSB, reg_2);

  return 0;
}

uint8_t RFM95WLORASetPreambleLength(uint16_t pre_length)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  uint8_t reg_buf[2] = {(uint8_t)(pre_length >> 8), (uint8_t)pre_length};

  RFM95WLORAWriteBurst(RFM95W_LORA_REG_PREAMBLE_MSB, reg_buf, 2);
  return 0;
}

uint8_t RFM95WLORASetPayloadLength(uint8_t payload_length)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  RFM95WLORAWriteSingle(RFM95W_LORA_REG_PAYLOAD_LENGTH, payload_length);
  return 0;
}

uint8_t RFM95WLORAReadPayloadLength()
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  return RFM95WLORAReadSingle(RFM95W_LORA_REG_PAYLOAD_LENGTH);
}

uint8_t RFM95WLORASetPayloadMaxLength(uint8_t payload_max_length)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  RFM95WLORAWriteSingle(RFM95W_LORA_REG_MAX_PAYLOAD_LENGTH, payload_max_length);
  return 0;
}


uint8_t RFM95WLORASetFifoAddrPtr(uint8_t addr)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  RFM95WLORAWriteSingle(RFM95W_LORA_REG_FIFO_ADDR_PTR, addr);
  return 0;
}

uint8_t RFM95WLORAReadFifoTxBase()
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  return RFM95WLORAReadSingle(RFM95W_LORA_REG_FIFO_TX_BASE_ADDR);
}

uint8_t RFM95WLORASetFifoTxBase(uint8_t tx_base_addr)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  RFM95WLORAWriteSingle(RFM95W_LORA_REG_FIFO_TX_BASE_ADDR, tx_base_addr);
  return 0;
}

uint8_t RFM95WLORAReadFifoRxBase()
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  return RFM95WLORAReadSingle(RFM95W_LORA_REG_FIFO_RX_BASE_ADDR);
}

uint8_t RFM95WLORASetFifoRxBase(uint8_t rx_base_addr)
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  RFM95WLORAWriteSingle(RFM95W_LORA_REG_FIFO_RX_BASE_ADDR, rx_base_addr);
  return 0;
}

uint8_t RFM95WLORAReadFifoRxNb()
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  return RFM95WLORAReadSingle(RFM95W_LORA_REG_RX_NB_BYTES);
}

uint8_t RFM95WLORAReadFifoRxDataAddr()
{
  if(RFM95WLORAReadMode() > RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  return RFM95WLORAReadSingle(RFM95W_LORA_REG_FIFO_RX_CURRENT_ADDR);
}


uint8_t RFM95WLORAWritePacket(uint8_t *data, uint8_t length)
{
  if(RFM95WLORAReadMode() != RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }

  RFM95WLORASetPayloadLength(length);
  uint8_t tx_base = RFM95WLORAReadFifoTxBase();

  RFM95WLORASetFifoAddrPtr(tx_base);
  RFM95WLORAWriteFIFO(RFM95W_LORA_REG_FIFO, data, length);

  return 0;
}

uint8_t RFM95WLORATransmitPacket(uint8_t *data, uint8_t length)
{
  if(RFM95WLORAWritePacket(data, length) == 0)
  {
    RFM95WLORASetMode(RFM95W_LORA_MODE_TX);
    return 0;
  }
  return (uint8_t)-1;
}


uint8_t RFM95WLORAReadPacket(uint8_t *data, uint8_t length)
{
  if(RFM95WLORAReadMode() != RFM95W_LORA_MODE_STDBY)
  {
    return (uint8_t)-1;
  }
  uint8_t count = RFM95WLORAReadFifoRxNb();
  uint8_t rx_data_base_addr = RFM95WLORAReadFifoRxDataAddr();
  if(!count)
  {
    return 0;
  }

  if(count > length)
  {
    return (uint8_t)-2;
  }

  RFM95WLORASetFifoAddrPtr(rx_data_base_addr);
  RFM95WLORAReadBurst(RFM95W_LORA_REG_FIFO, data, count);

  return count;
}
