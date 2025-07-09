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
// kirim reqa dan atqa
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

// konstanta dan helper
#define PICC_ANTICOLL  0x93
#define PICC_SElECTTAG 0x93
#define PICC_AUTHENT1A 0x60
#define PICC_AUTHENT1B 0x61
#define PICC_READ      0x30

#define Status_OK         0
#define Status_ERROR      1
#define MAX_LEN 16

#define PCD_TRANSCEIVE   0x0C
#define PCD_IDLE         0x00 // nilai posisi idle 
#define PCD_RESETPHASE   0x0F // nilai untuk reset

// crc calculate
#define DivIrqReg      0x05
#define CRCResultRegL  0x22
#define CRCResultRegM  0x21
#define PCD_CALCCRC    0x03

// auth
#define Status2Reg     0x08
#define PCD_AUTHENT    0x0E


#define MFRC522_CS_GPIO      32 //gpio untuk esp32
#define MFRC522_RST_GPIO     13

esp_err_t rc522_init(spi_host_device_t spi_host);
uint8_t rc522_read_reg(uint8_t reg);
void rc522_write_reg(uint8_t reg, uint8_t val);

void rc522_antenna_on(); //enable antena

bool rc522_request(uint8_t *atqa); // REQA dan ATQA
bool rc522_anticoll(uint8_t *uid);

// otentikasi
esp_err_t rc522_auth(uint8_t auth_mode, uint8_t block_addr, uint8_t *key, uint8_t *uid);
esp_err_t rc522_read_block(uint8_t block_addr, uint8_t *block_data);
