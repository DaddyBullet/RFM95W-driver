#ifndef RFM95W_LORA_DEFINES_H
#define RFM95W_LORA_DEFINES_H

#include <stdint.h>

#define UPPER_REGESTRY_DESCRIPTION 0
#if UPPER_REGESTRY_DESCRIPTION == 1
typedef enum{
  RFM95W_LORA_REG_FIFIO = 0x00,
  RFM95W_LORA_REG_OP_MODE,

  RFM95W_LORA_REG_FRF_MSB = 0x06,
  RFM95W_LORA_REG_FRF_MID,
  RFM95W_LORA_REG_FRF_LSB,

  RFM95W_LORA_REG_PA_CONFIG,
  RFM95W_LORA_REG_PA_RAMP,

  RFM95W_LORA_REG_OCP,
  RFM95W_LORA_REG_LNA,

  RFM95W_LORA_REG_FIFO_ADDR_PTR,
  RFM95W_LORA_REG_FIFO_TX_BASE_ADDR,

  RFM95W_LORA_REG_IRQ_FLAGS,
  RFM95W_LORA_REG_IRQ_FLAGS_MASK,

  RFM95W_LORA_REG_FREQ_IF_MSB,
  RFM95W_LORA_REG_FREQ_IF_LSB,

  RFM95W_LORA_REG_SYMB_TIMEOUT_MSB,
  RFM95W_LORA_REG_SYMB_TIMEOUT_LSB,

  RFM95W_LORA_REG_TX_CFG,
  RFM95W_LORA_REG_PAYLOAD_LENGTH,

  RFM95W_LORA_REG_PREAMBLE_MSB,
  RFM95W_LORA_REG_PREAMBLE_LSB,

  RFM95W_LORA_REG_MODULATION_CFG,

  RFM95W_LORA_REG_RF_MODE,

  RFM95W_LORA_REG_HOP_PERIOD,

  RFM95W_LORA_REG_NB_RX_BYTES,

  RFM95W_LORA_REG_RX_HEADER_INFO,
  RFM95W_LORA_REG_RX_HEADER_CNT_VALUE,
  RFM95W_LORA_REG_RX_PACKET_CNT_VALUE,

  RFM95W_LORA_REG_MODEM_STAT,

  RFM95W_LORA_REG_PKT_SNR_VALUE,

  RFM95W_LORA_REG_RSSI_VALUE,
  RFM95W_LORA_REG_PKT_RSSI_VALUE,

  RFM95W_LORA_REG_HOP_CHANNEL,

  RFM95W_LORA_REG_RX_DATA_ADDR,

  RFM95W_LORA_REG_DIO_MAPPING1 = 0x40,
  RFM95W_LORA_REG_DIO_MAPPING2,

  RFM95W_LORA_REG_VERSION,

  RFM95W_LORA_REG_TCXO = 0x44,

  RFM95W_LORA_REG_PA_DAC,

  RFM95W_LORA_REG_FORMER_TEMP,

  RFM95W_LORA_REG_AGC_REF = 0x61,
  RFM95W_LORA_REG_AGC_THRESH1,
  RFM95W_LORA_REG_AGC_THRESH2,
  RFM95W_LORA_REG_AGC_THRESH3,
}RFM95W_LORA_REG_ADDR;
#else
typedef enum{
  RFM95W_LORA_REG_FIFIO = 0x00,
  RFM95W_LORA_REG_OP_MODE,

  RFM95W_LORA_REG_FRF_MSB = 0x06,
  RFM95W_LORA_REG_FRF_MID,
  RFM95W_LORA_REG_FRF_LSB,

  RFM95W_LORA_REG_PA_CONFIG,
  RFM95W_LORA_REG_PA_RAMP,

  RFM95W_LORA_REG_OCP,
  RFM95W_LORA_REG_LNA,

  RFM95W_LORA_REG_FIFO_ADDR_PTR,
  RFM95W_LORA_REG_FIFO_TX_BASE_ADDR,
  RFM95W_LORA_REG_FIFO_RX_BASE_ADDR,
  RFM95W_LORA_REG_FIFO_RX_CURRENT_ADDR,

  RFM95W_LORA_REG_IRQ_FLAGS_MASK,
  RFM95W_LORA_REG_IRQ_FLAGS,

  RFM95W_LORA_REG_RX_NB_BYTES,

  RFM95W_LORA_REG_RX_HEADER_CNT_VALUE_MSB,
  RFM95W_LORA_REG_RX_HEADER_CNT_VALUE_LSB,

  RFM95W_LORA_REG_RX_PACKET_CNT_VALUE_MSB,
  RFM95W_LORA_REG_RX_PACKET_CNT_VALUE_LSB,

  RFM95W_LORA_REG_MODEM_STAT,

  RFM95W_LORA_REG_PKT_SNR_VALUE,

  RFM95W_LORA_REG_PKT_RSSI_VALUE,
  RFM95W_LORA_REG_RSSI_VALUE,

  RFM95W_LORA_REG_HOP_CHANNEL,

  RFM95W_LORA_REG_MODEM_CONFIG,
  RFM95W_LORA_REG_MODEM_CONFIG_2,

  RFM95W_LORA_REG_SYMB_TIMEOUT_LSB,

  RFM95W_LORA_REG_PREAMBLE_MSB,
  RFM95W_LORA_REG_PREAMBLE_LSB,

  RFM95W_LORA_REG_PAYLOAD_LENGTH,

  RFM95W_LORA_REG_MAX_PAYLOAD_LENGTH,

  RFM95W_LORA_REG_HOP_PERIOD,

  RFM95W_LORA_REG_FIFO_RX_BYTE_ADDR,
  RFM95W_LORA_REG_MODEM_CONFIG_3,

  RFM95W_LORA_REG_DIO_MAPPING1 = 0x40,
  RFM95W_LORA_REG_DIO_MAPPING2,

  RFM95W_LORA_REG_VERSION,

  RFM95W_LORA_REG_TCXO = 0x44,

  RFM95W_LORA_REG_PA_DAC,

  RFM95W_LORA_REG_FORMER_TEMP,

  RFM95W_LORA_REG_AGC_REF = 0x61,
  RFM95W_LORA_REG_AGC_THRESH1,
  RFM95W_LORA_REG_AGC_THRESH2,
  RFM95W_LORA_REG_AGC_THRESH3,
}RFM95W_LORA_REG_ADDR;
#endif /* UPPER_REGESTRY_DESCRIPTION == 1 */


// LORA RegOpMode Bits
typedef enum{
  RFM95W_LORA_MODE_SLEEP = 0x00,
  RFM95W_LORA_MODE_STDBY,
  RFM95W_LORA_MODE_FSTX,
  RFM95W_LORA_MODE_TX,
  RFM95W_LORA_MODE_FSRX,
  RFM95W_LORA_MODE_RXCONTINUOS,
  RFM95W_LORA_MODE_RXSINGLE,
  RFM95W_LORA_MODE_CAD,
}RFM95W_LORA_MODE;

#define RFM95W_LORA_LORA_MODE 0x01
#define RFM95W_LORA_FSK_MODE  0x00

#define RFM95W_LORA_ACCESS_SHARED_REG_ON  0x01
#define RFM95W_LORA_ACCESS_SHARED_REG_OFF 0x00

#define RFM95W_LORA_LOW_FREQ_MODE   0x01
#define RFM95W_LORA_HIHG_GREQ_MODE  0x00
// End LORA RegOpMode Bits

typedef enum{
  RFM95W_LORA_IRQ_FLAG_CAD_DETECTED        = 0x01,
  RFM95W_LORA_IRQ_FLAG_FHSS_CHANGE_CHANNEL = 0x02,
  RFM95W_LORA_IRQ_FLAG_CAD_DONE            = 0x04,
  RFM95W_LORA_IRQ_FLAG_TX_DONE             = 0x08,
  RFM95W_LORA_IRQ_FLAG_VALID_HEADER        = 0x10,
  RFM95W_LORA_IRQ_FLAG_PAYLOAD_CRC_ERROR   = 0x20,
  RFM95W_LORA_IRQ_FLAG_RX_DONE             = 0x40,
  RFM95W_LORA_IRQ_FLAG_RX_TIMEOUT          = 0x80,
}RFM95W_LORA_IRQ_FLAG;

// LORA RegPaConfig Bits
#define RFM95W_LORA_PA_SELECT_14DBM 0x00
#define RFM95W_LORA_PA_SELECT_20DBM 0x01
// End LORA RegPaConfig Bits

// LORA RegOcp Bits
#define RFM95W_LORA_OCP_ON  0x01
#define RFM95W_LORA_OCP_OFF 0x00
// End LORA RegOcp Bits

// LORA ModemConfig Bits
typedef enum{
  RFM95W_LORA_BANDWIDTH_7800   = 0x00,
  RFM95W_LORA_BANDWIDTH_10400,
  RFM95W_LORA_BANDWIDTH_15600,
  RFM95W_LORA_BANDWIDTH_20800,
  RFM95W_LORA_BANDWIDTH_31250,
  RFM95W_LORA_BANDWIDTH_41700,
  RFM95W_LORA_BANDWIDTH_62500,
  RFM95W_LORA_BANDWIDTH_125000,
  RFM95W_LORA_BANDWIDTH_250000,
  RFM95W_LORA_BANDWIDTH_500000,
}RFM95W_LORA_BANDWIDTH;

typedef enum{
  RFM95W_LORA_CR_4_5 = 0x01,
  RFM95W_LORA_CR_4_6,
  RFM95W_LORA_CR_4_7,
  RFM95W_LORA_CR_4_8,
}RFM95W_LORA_CR;

typedef enum{
  RFM95W_LORA_SF_6 = 0x06,
  RFM95W_LORA_SF_7,
  RFM95W_LORA_SF_8,
  RFM95W_LORA_SF_9,
  RFM95W_LORA_SF_10,
  RFM95W_LORA_SF_11,
  RFM95W_LORA_SF_12,
}RFM95W_LORA_SF;

typedef enum{
  RFM95W_LORA_HEADER_MODE_EXPLICIT = 0x00,
  RFM95W_LORA_HEADER_MODE_IMPLICIT = 0x01,
}RFM95W_LORA_HEADER_MODE;

typedef enum{
  RFM95W_LORA_TX_MODE_NORMAL = 0x00,
  RFM95W_LORA_TX_MODE_CONTINUOUS = 0x01,
}RFM95W_LORA_TX_MODE;

typedef enum{
  RFM95W_LORA_RX_PAYLOAD_CRC_OFF = 0x00,
  RFM95W_LORA_RX_PAYLOAD_CRC_ON = 0x01,
}RFM95W_LORA_RX_PAYLOAD_CRC;

typedef enum{
  RFM95W_LORA_NODE_STATIC = 0x00,
  RFM95W_LORA_NODE_MOBILE = 0x01,
}RFM95W_LORA_NODE;

typedef enum{
  RFM95W_LORA_AGC_AUTO_OFF = 0x00,
  RFM95W_LORA_AGC_AUTO_ON  = 0x01,
}RFM95W_LORA_AGC_AUTO;

// End LORA ModemConfig Bits
#endif /* RFM95W_LORA_DEFINES_H */
