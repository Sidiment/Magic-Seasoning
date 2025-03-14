#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <driver/i2s.h>

// BLE UUIDs
#define SERVICE_UUID        "26ce00bb-a003-4ea7-a2a1-235fbe0eacab"
#define CHARACTERISTIC_UUID "0195880f-84bd-72d2-b488-34d1ca5af16a"

// BLE characteristic
BLECharacteristic *pCharacteristic;

// I2S microphone pins
#define I2S_WS 11
#define I2S_SD 10
#define I2S_SCK 12

// Use I2S Processor 0
#define I2S_PORT I2S_NUM_0

// Buffer for I2S data
#define bufferLen 64
int16_t sBuffer[bufferLen];

void i2s_install() {
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = i2s_bits_per_sample_t(16),
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = bufferLen,
    .use_apll = false
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}

void i2s_setpin() {
  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };

  i2s_set_pin(I2S_PORT, &pin_config);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE Server with I2S Microphone!");

  // Initialize BLE
  BLEDevice::init("ESP32 Mic Server");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );

  pCharacteristic->setValue("Waiting for data...");
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("BLE Server is running. Clients can now connect.");

  // Setup I2S Microphone
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);
}

void loop() {
  size_t bytesIn = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);

  if (result == ESP_OK) {
    int16_t samples_read = bytesIn / 8;
    if (samples_read > 0) {
      float mean = 0;
      for (int16_t i = 0; i < samples_read; ++i) {
        mean += sBuffer[i];
      }

      mean /= samples_read;

      // Convert mean value to string and update BLE characteristic
      String meanValue = String(mean);
      pCharacteristic->setValue(meanValue.c_str());
      pCharacteristic->notify();  // Send update to client

      Serial.print("Mean Sound Level: ");
      Serial.println(mean);
    }
  }

  delay(1000); // Send updates every second
}
