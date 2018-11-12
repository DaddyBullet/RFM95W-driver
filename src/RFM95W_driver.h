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
// This will put modem in LORA mode
uint8_t RFM95WLORAInitRegOpMode(uint8_t access_share_reg, uint8_t low_freq_mode_on, uint8_t mode);




#endif /* RFM95W_DRIVER_H */
