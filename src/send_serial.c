#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void send_file_over_serial(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        printf("Gagal membuka file %s untuk dibaca.\n", path);
        return;
    }
    printf("===BEGIN_DUMP===\n");
    // printf("Mengirim file %s melalui serial...\n", path);

    uint8_t buffer[128];
    size_t read_bytes;

    while ((read_bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, read_bytes, stdout);
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(10)); // beri waktu UART stabil
    }
    fclose(file);
    printf("\nSelesai mengirim file.\n");
    printf("===END_DUMP===\n");
}
