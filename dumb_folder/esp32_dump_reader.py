import serial

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)  # ganti sesuai port ESP32 kamu
output_file = "dump_downloaded.bin"
capture = False
buffer = b""

print(f"Menerima data dan menyimpan ke {output_file} ...")

with open(output_file, "wb") as f:
    while True:
        data = ser.read(128)  # baca chunk data
        if not data:
            continue

        buffer += data

        if not capture:
            if b"===BEGIN_DUMP===" in buffer:
                capture = True
                print("Tag BEGIN_DUMP terdeteksi, mulai capture.")
                # Buang semua sebelum tag
                buffer = buffer.split(b"===BEGIN_DUMP===")[1]
        if capture:
            if b"===END_DUMP===" in buffer:
                print("Tag END_DUMP terdeteksi, selesai capture.")
                # Ambil hanya data sebelum tag END
                data_to_write = buffer.split(b"===END_DUMP===")[0]
                f.write(data_to_write)
                break
            else:
                # Tulis semua buffer jika END belum ketemu, kosongkan buffer
                f.write(buffer)
                buffer = b""

print(f"Dump selesai, file disimpan sebagai {output_file}")
        
