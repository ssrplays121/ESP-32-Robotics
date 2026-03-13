#include <esp_now.h>
#include <WiFi.h>

// FORMAT: 0x followed by the hex characters
// Put Device A's MAC address here:
uint8_t senderAddress[] = {0xB0,0xCB,0xD8,0x04,0x0C,0x54}; 

esp_now_peer_info_t peerInfo;

// UPDATED CALLBACK for newer ESP32 cores
void OnDataRecv(const esp_now_recv_info * info, const uint8_t *incomingData, int len) {
  // Immediately echo the exact same data back to Device A
  esp_now_send(senderAddress, incomingData, len);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the receive callback
  esp_now_register_recv_cb(OnDataRecv);

  // Register Device A as a peer so we can reply to it
  memcpy(peerInfo.peer_addr, senderAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void loop() {
  // The loop is empty. Everything is handled instantly by the receive callback!
}