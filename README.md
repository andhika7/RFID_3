Code RFID dengan ESP32 dan RC522 dengan ESP-IDF PlatformIO:
Alur code :
  1. Deteksi kartu (rc522_request)
  2. Baca UID (rc522_anticoll)
  3. Select UID (rc522_select)
  4. Brute_force_key_finder (brute force key A)
  5. Jika key ditemukan, Auth dengan key tersebut
  6. Re-select UID sebelum auth ulang
  7. Autentikasi (rc522_auth)
  8. Read data (rc522_read_block)
