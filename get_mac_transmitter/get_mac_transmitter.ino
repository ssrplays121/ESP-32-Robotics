#include <esp_mac.h> // Include for esp_read_mac function
// B0:CB:D8:04:0C:54
void setup() {
  Serial.begin(115200);
  delay(1000);

  uint8_t baseMac[6];
  // Get MAC address for WiFi station
  esp_read_mac(baseMac, ESP_MAC_WIFI_STA);

  Serial.print("Base MAC Address: ");
  for (int i = 0; i < 5; i++) {
    Serial.printf("%02X:", baseMac[i]);
  }
  Serial.printf("%02X\n", baseMac[5]);
}

void loop() {
}