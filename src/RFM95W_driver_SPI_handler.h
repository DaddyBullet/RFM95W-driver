#ifndef _RFM95W_DRIVER_SPI_HANDLER_H
#define _RFM95W_DRIVER_SPI_HANDLER_H

#include "RFM95W_LORA_defines.h"

uint8_t RFM95WLORAReadSingle(RFM95W_LORA_REG_ADDR addr);
void RFM95WLORAReadBurst(RFM95W_LORA_REG_ADDR addr, uint8_t *read_data, uint8_t read_data_size);
void RFM95WLORAReadFIFO(RFM95W_LORA_REG_ADDR addr, uint8_t *read_data, uint8_t read_data_size);

void RFM95WLORAWriteSingle(RFM95W_LORA_REG_ADDR addr, uint8_t write_data);
void RFM95WLORAWriteBurst(RFM95W_LORA_REG_ADDR addr, uint8_t* write_data, uint8_t write_data_size);
void RFM95WLORAWriteFIFO(RFM95W_LORA_REG_ADDR addr, uint8_t* write_data, uint8_t write_data_size);

#endif // _RFM95W_DRIVER_SPI_HANDLER_H
