#include <esp_now.h>
#include <WiFi.h>

// user defined structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

struct_message myData;

uint8_t receiverAddress[] = {0x30, 0x30, 0xF9, 0x72, 0x10, 0xAC};

// callback when data is sent
void OnDataSent(const wifi_tx_info_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);

  // set ESP32 as a wifi Station
  WiFi.mode(WIFI_STA);
  Serial.print("Sender MAC Address: ");
  Serial.println(WiFi.macAddress());

  // init esp_now
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // register the send callback
  esp_now_register_send_cb(OnDataSent);

  // register peer (receiver)
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  strcpy(myData.a, "Hello My Name is Asad Iqbal");
  myData.b = random(0, 100);
  myData.c = 5.5;
  myData.d = true;

  // send message
  esp_err_t result = esp_now_send(receiverAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Message sent successfully");
  } else {
    Serial.println("Error sending message");
  }

  delay(5000);  
}
