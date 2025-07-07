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
        while (1) vTaskDelay(pdMS_TO_TICKS(1000));
    }

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
