// Receiver ESP32 Code

#include <SPI.h>
#include <SD.h>
#include <esp_now.h>
#include <WiFi.h>


#define SD_CS_PIN 5

// Struktur data yang diterima
typedef struct struct_message {
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
} struct_message;

// File untuk menyimpan data
File dataFile;

// Callback untuk penerimaan data
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  struct_message receivedData;
  memcpy(&receivedData, incomingData, sizeof(receivedData));

  // Menulis data ke file CSV
  dataFile.print(receivedData.ax);
  dataFile.print(",");
  dataFile.print(receivedData.ay);
  dataFile.print(",");
  dataFile.print(receivedData.az);
  dataFile.print(",");
  dataFile.print(receivedData.gx);
  dataFile.print(",");
  dataFile.print(receivedData.gy);
  dataFile.print(",");
  dataFile.println(receivedData.gz);
  
  dataFile.flush(); // utnuk memastikan data tersimpan 

  Serial.println("Data diterima dan disimpan");
}

void setup() {
  // Inisialisasi serial
  Serial.begin(115200);
  Serial.println("Receiver ESP32");

  // Inisialisasi SD Card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Inisialisasi SD Card gagal!");
    while (1);
  }
  Serial.println("SD Card siap");

  // Membuka atau membuat file CSV
  dataFile = SD.open("/data.csv", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Tidak dapat membuka data.csv");
    while (1);
  }

  // Menulis header CSV jika file baru
  if (dataFile.size() == 0) {
    dataFile.println("ax,ay,az,gx,gy,gz");
    dataFile.flush();
  }

  // Inisialisasi WiFi dalam mode STA
  WiFi.mode(WIFI_STA);
  
  // Menampilkan alamat MAC receiver
  Serial.print("Alamat MAC Receiver: ");
  Serial.println(WiFi.macAddress());

  // Inisialisasi ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Inisialisasi ESP-NOW gagal");
    while (1);
  }
  Serial.println("ESP-NOW diinisialisasi");

  // Mendaftarkan callback penerimaan
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Receiver siap");
}

void loop() {
 
}

