#include <SPI.h>       // Pustaka SPI untuk berkomunikasi dengan modul LoRa
#include <LoRa.h>      // Pustaka LoRa untuk mengontrol modul LoRa

// Definisi pin yang digunakan untuk LoRa di ESP32
#define SS 5           // Pin Slave Select (SS) untuk SPI
#define RST 14         // Pin Reset untuk modul LoRa
#define DIO0 2         // Pin DIO0 digunakan untuk interupsi modul LoRa

void setup() {
  Serial.begin(9600);  // Memulai komunikasi serial dengan baudrate 9600
  while (!Serial);     // Tunggu hingga serial siap

  // Atur pin modul LoRa menggunakan fungsi setPins
  LoRa.setPins(SS, RST, DIO0);

  // Inisialisasi LoRa pada frekuensi 915 MHz (atau frekuensi lain sesuai modul LoRa Anda)
  if (!LoRa.begin(915E6)) { // Jika LoRa gagal diinisialisasi, cetak pesan kesalahan
    Serial.println("Gagal menginisialisasi LoRa!");
    while (1); // Hentikan eksekusi jika LoRa gagal
  }
  Serial.println("LoRa receiver siap."); // Konfirmasi bahwa receiver siap
}

void loop() {
  // Periksa apakah ada paket data yang diterima
  int packetSize = LoRa.parsePacket(); 
  if (packetSize) {
    // Jika ada paket yang diterima, baca dan tampilkan pesan
    Serial.print("Pesan diterima: ");

    while (LoRa.available()) {
      String pesan = LoRa.readString(); // Baca pesan yang diterima
      Serial.print(pesan); // Tampilkan pesan di serial monitor
    }
    Serial.println(); // Tambahkan baris baru setelah pesan diterima
  }
}
