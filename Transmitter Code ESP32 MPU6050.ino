// Transmitter ESP32 Code

#include <Wire.h>
#include <MPU6050.h>
#include <esp_now.h>
#include <WiFi.h>

// Inisialisasi objek MPU6050
MPU6050 mpu;

// Struktur data yang akan dikirim
typedef struct struct_message {
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
} struct_message;

// Membuat instance pesan
struct_message myData;

// Alamat MAC penerima (Ganti dengan alamat MAC ESP32 receiver)
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xAB, 0xCD, 0xEF};

// Callback untuk pengiriman data
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Data berhasil dikirim");
  } else {
    Serial.println("Pengiriman data gagal");
  }
}

void setup() {
  // Inisialisasi serial
  Serial.begin(115200);
  Serial.println("Transmitter ESP32");

  // Inisialisasi I2C
  Wire.begin();

  // Inisialisasi MPU6050
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 tidak terhubung!");
    while (1);
  }
  Serial.println("MPU6050 terhubung");

  // Inisialisasi WiFi dalam mode STA
  WiFi.mode(WIFI_STA);

  // Inisialisasi ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Inisialisasi ESP-NOW gagal");
    while (1);
  }
  Serial.println("ESP-NOW diinisialisasi");

  // Mendaftarkan callback pengiriman
  esp_now_register_send_cb(OnDataSent);

  // Menambahkan receiver
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  // Menambahkan peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Menambahkan peer gagal");
    while (1);
  }
  Serial.println("Peer ditambahkan");
}

void loop() {
  // Membaca data MPU6050
  myData.ax = mpu.getAccelerationX();
  myData.ay = mpu.getAccelerationY();
  myData.az = mpu.getAccelerationZ();
  myData.gx = mpu.getRotationX();
  myData.gy = mpu.getRotationY();
  myData.gz = mpu.getRotationZ();

  // Mengirim data
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  // Delay antara pengiriman (misalnya 100ms)
  delay(100);
}

