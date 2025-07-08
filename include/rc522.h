#pragma once

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "stdint.h"

// register dan alamat register
#define CommandReg      0x01 
#define ModeReg         0x11
#define TxControlReg    0x14
#define VersionReg      0x37
#define FIFOLevelReg    0x0A
#define FIFODataReg     0x09
#define BitFramingReg   0x0D
#define CommIrqReg      0x04
#define ErrorReg        0x06

#define TModeReg        0x2A
#define TPrescalerReg   0x2B
#define TReloadRegL     0x2D
#define TReloadRegH     0x2C
#define TxASKReg        0x15



#define PCD_TRANSCEIVE   0x0C
#define PCD_IDLE         0x00 // nilai posisi idle 
#define PCD_RESETPHASE   0x0F // nilai untuk reset


#define MFRC522_CS_GPIO      32 //gpio untuk esp32
#define MFRC522_RST_GPIO     13

esp_err_t rc522_init(spi_host_device_t spi_host);
uint8_t rc522_read_reg(uint8_t reg);
void rc522_write_reg(uint8_t reg, uint8_t val);

void rc522_antenna_on(); //enable antena

bool rc522_request(uint8_t *atqa); // REQA dan ATQA

