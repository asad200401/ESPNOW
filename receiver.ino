#include <esp_now.h>
#include <WiFi.h>

// user defined structure same as sender
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

struct_message incomingData;

// callback when data is received
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingDataBytes, int len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));

  Serial.println("Received data:");
  Serial.print("a: "); Serial.println(incomingData.a);
  Serial.print("b: "); Serial.println(incomingData.b);
  Serial.print("c: "); Serial.println(incomingData.c);
  Serial.print("d: "); Serial.println(incomingData.d ? "true" : "false");
  Serial.println("-------------------------");
}

void setup() {
  Serial.begin(115200);

  // set ESP32-S3 as a wifi Station
  WiFi.mode(WIFI_STA);
  Serial.print("Receiver MAC Address: ");
  Serial.println(WiFi.macAddress());

  // init esp_now
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // register the receive callback
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
 
}
