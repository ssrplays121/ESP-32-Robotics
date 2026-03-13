#include <esp_now.h>
#include <WiFi.h>

// FORMAT: 0x followed by the hex characters
// Put Device B's MAC address here:
uint8_t receiverAddress[] = {0xB0,0xCB,0xD8,0x03,0x8E,0x7C}; 

typedef struct struct_message {
  unsigned long timestamp;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

// UPDATED CALLBACK for newer ESP32 cores
void OnDataRecv(const esp_now_recv_info * info, const uint8_t *incomingData, int len) {
  unsigned long current_time = micros();
  
  // Copy incoming data into our struct
  memcpy(&myData, incomingData, sizeof(myData));
  
  unsigned long rtt = current_time - myData.timestamp;
  
  Serial.print("Round Trip Time: ");
  Serial.print(rtt);
  Serial.print(" us | One-way Latency: ");
  Serial.print(rtt / 2.0);
  Serial.println(" us");
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

  // Register Device B as a peer
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void loop() {
  // Record current time and send it to Device B
  myData.timestamp = micros();
  esp_now_send(receiverAddress, (uint8_t *) &myData, sizeof(myData));
  
  delay(1000); // Send a ping every 1 second
}