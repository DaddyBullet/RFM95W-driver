#ifndef RFM95W_DRIVER_H
#define RFM95W_DRIVER_H

#include "RFM95W_LORA_defines.h"
#include "RFM95W_driver_SPI_handler.h"

uint8_t RFM95WLORASetMode(RFM95W_LORA_MODE mode);
uint8_t RFM95WLORASetLoraFsk(uint8_t global_mode);
uint8_t RFM95WLORASetFreqMode(uint8_t freq_mode);




#endif /* RFM95W_DRIVER_H */
