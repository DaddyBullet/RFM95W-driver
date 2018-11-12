#ifndef RFM95W_DRIVER_H
#define RFM95W_DRIVER_H

#include "RFM95W_LORA_defines.h"
#include "RFM95W_driver_SPI_handler.h"

uint8_t RFM95WLORASetIrqFlagsMask(uint8_t mask);
uint8_t RFM95WLORAReadIrqFlagsMask();

uint8_t RFM95WLORAReadIrqFlags();
uint8_t RFM95WLORAClearIrqFlags(uint8_t mask);

uint8_t RFM95WLORAReadIrqFlag(RFM95W_LORA_IRQ_FLAG flag);
uint8_t RFM95WLORAClearIrqFlag(RFM95W_LORA_IRQ_FLAG flag);

RFM95W_LORA_MODE RFM95WLORAReadMode();

uint8_t RFM95WLORASetMode(RFM95W_LORA_MODE mode);
uint8_t RFM95WLORASetLoraFsk(uint8_t global_mode);
uint8_t RFM95WLORASetFreqMode(uint8_t freq_mode);

uint8_t RFM95WLORASetFreq(uint32_t freq, uint32_t xosc_freq);
uint8_t RFM95WLORASetFreq868();
// This will put modem in LORA mode
uint8_t RFM95WLORAInitRegOpMode(uint8_t access_share_reg, uint8_t low_freq_mode_on, uint8_t mode);

uint8_t RFM95WLORASetPaConfig(uint8_t pa_select, uint8_t max_power, uint8_t output_power);
uint8_t RFM95WLORASetPaSelect(uint8_t pa_select);
// Pmax = 10.8 + (0.6 * max_power) [dBm]
uint8_t RFM95WLORASetPaMaxPower(uint8_t max_power);
// Pout = Pmax - (15 - output_power) if pa_select == 0
// Pout = 17  -  (15 - output_power) if pa_select == 1
uint8_t RFM95WLORASetPaOutputPower(uint8_t output_power);

uint8_t RFM95WLORASetOcpConfig(uint8_t osp_on, uint8_t ocp_trim);
uint8_t RFM95WLORASetOcpOn(uint8_t osp_on);
// Imax = 45 + (5 * osp_trim) [mA] if osp_trim <= 15
// Imax = -30 + (10 * osp_trim) [mA] if 15 < osp_trim <= 27
// Imax = 100[mA] if osp_trim > 27
uint8_t RFM95WLORASetOcpTrim(uint8_t osp_trim);

uint8_t RFM95WLORASetLnaConfig(uint8_t lna_gain, uint8_t lna_boost_lf, uint8_t lna_boost_hf);

#endif /* RFM95W_DRIVER_H */
