#include <BluetoothSerial.h>  // Mengimpor library Bluetooth Serial
BluetoothSerial SerialBT;     // Inisialisasi objek Serial Bluetooth

void setup() {
  Serial.begin(115200);                  // Memulai komunikasi serial ESP32 pada baud rate 115200
  SerialBT.begin("SAPUANGINITSTEAM");     // Memulai Bluetooth dengan nama "SAPUANGINITSTEAM"
  Serial.println("Bluetooth Serial Getting Started!");  // Pesan saat Bluetooth dimulai
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());       // Jika ada data yang diterima dari Serial, kirim melalui Bluetooth
    String dataTosend = Serial.readString();  
    array(dataTosend);                   // Kirim data dalam bentuk string ke dalam fungsi array
  }
  
  if (SerialBT.available()) {
    send();                        // Panggil fungsi pengiriman (send) untuk mengirimkan data
    Serial.write(SerialBT.read());       // Jika ada data dari Bluetooth, kirim ke Serial Monitor
  }

  delay(1000);  // Penundaan 1 detik
}

// Fungsi untuk mencetak karakter string satu per satu
void array(String nilai) {
  int data = nilai.length();
  for (int i = 0; i < data; i++) {
    SerialBT.println(nilai[i]);  // Mengirimkan setiap karakter string melalui Bluetooth
    delay(2000);                // Delay 2000 milisecond setiap pengiriman karakter
  }
}

// Fungsi pengiriman untuk mengirimkan data RPM, Speed, TPS, dan Temperature
void send() {
  // Deklarasi variabel
  int rpm = 6789;               // RPM per minute
  float speed = 123.45;          // Kecepatan dalam km/h
  int tps = 85;                  // Throttle Position dalam persen
  float temperature = 98.76;     // Temperatur dalam derajat Celsius

  // Konversi nilai ke String untuk pengiriman satu per satu
  String rpmString = String(rpm);
  String speedString = String(speed);
  String tpsString = String(tps);
  String temperatureString = String(temperature);

  // Mengirim nilai RPM
  SerialBT.println("RPM: ");
  for (int i = 0; i < rpmString.length(); i++) {
    SerialBT.println(rpmString[i]);  // Mengirimkan tiap karakter dari RPM
    delay(1000);                     // Penundaan 1 detik
  }

  // Mengirim nilai Speed
  SerialBT.println("Speed: ");
  for (int i = 0; i < speedString.length(); i++) {
    SerialBT.println(speedString[i]);  // Mengirimkan tiap karakter dari Speed
    delay(1000);                       // Penundaan 1 detik
  }

  // Mengirim nilai TPS
  SerialBT.println("TPS: ");
  for (int i = 0; i < tpsString.length(); i++) {
    SerialBT.println(tpsString[i]);  // Mengirimkan tiap karakter dari TPS
    delay(1000);                     // Penundaan 1 detik
  }

  // Mengirim nilai Temperature
  SerialBT.println("Temperature: ");
  for (int i = 0; i < temperatureString.length(); i++) {
    SerialBT.println(temperatureString[i]);  // Mengirimkan tiap karakter dari Temperature
    delay(1000);                            // Penundaan 1 detik
  }

  delay(2000);  // Penundaan 2 detik setelah mengirim semua data
}
