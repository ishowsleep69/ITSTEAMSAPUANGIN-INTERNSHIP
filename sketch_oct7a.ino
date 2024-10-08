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
  Serial.println("LoRa transmitter siap."); // Konfirmasi bahwa transmitter siap
}

void loop() {
  Serial.print("Mengirim pesan: ");
  Serial.println("Halo dari transmitter ESP32!"); // Pesan yang akan dikirim

  // Memulai paket pengiriman
  LoRa.beginPacket();
  LoRa.print("Halo dari transmitter ESP32!"); // Menulis pesan ke paket LoRa
  LoRa.endPacket();  // Mengakhiri paket pengiriman

  delay(5000); // Menunggu 5 detik sebelum mengirim pesan berikutnya