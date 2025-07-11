#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rc522.h"

void app_main(void) {
    // printf("Memulai inisialisasi RC522...\n");

    if (rc522_init(VSPI_HOST) == ESP_OK) { // VSPI_HOST = menghubungkan perangkat SPI external seperti rc522
        printf("RC522 Init Sukses\n");
        // setelah bisa inisialisasi, mengaktifkan antena
        rc522_antenna_on();
        vTaskDelay(pdMS_TO_TICKS(100));

        // Cek status antena
        uint8_t tx_ctrl = rc522_read_reg(TxControlReg);
        printf("TxControlReg: 0x%02X\n", tx_ctrl);
        

    } else {
        printf("RC522 Init Gagal\n");
        // while (1) vTaskDelay(pdMS_TO_TICKS(1000));
    }

    uint8_t atqa[2]; //ATQA
    uint8_t uid[5];

    while (1) {
        if (rc522_request(atqa)) {
            printf("Kartu Terdeteksi! ATQA: %02X %02X\n", atqa[0], atqa[1]);
            if (rc522_anticoll(uid)){
                printf("UID: ");
                for (int i = 0; i < 4; i++){
                    printf("%02x ", uid[i]);
                }
                printf("\n");
                // uint8_t block_data[16];

                if (rc522_select(uid) == Status_OK){
                    printf("Select UID berhasil.\n");
                    vTaskDelay(pdMS_TO_TICKS(100)); // Tambah delay setelah select
                    uint8_t found_key[6];
                    
                    if (brute_force_key_finder(uid, found_key)){
                        // Tampilkan key hasil brute
                        printf("Key ditemukan hasil brute force: ");
                        for (int i = 0; i < 6; i++){
                            printf("%02X ", found_key[i]);
                        }
                        printf("\n");
                    }
                    
                } else {
                    printf("Select UID gagal.\n");
                }

            } else {
                printf("gagal membaca UID\n");
            }
        } else {
            printf("Tidak ada kartu.\n");
        }        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
