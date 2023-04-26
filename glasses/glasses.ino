/*
TRANSMITER
*/

#include <esp_now.h>
#include <WiFi.h>

#define left 21
#define right 12
#define front 23

// REPLACE WITH YOUR RECEIVER MAC Address
// EC:62:60:1E:C3:44

uint8_t broadcastAddress[] = {0xEC, 0x62, 0x60, 0x1E, 0xC3, 0x44};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int m;
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // Set values to send
// myData.m = 5;
myData.m =5;
if (digitalRead(left) == 1 and digitalRead(right) == 1 and digitalRead(front) == 1){
  // left
myData.m =-2;
}  
else if (digitalRead(left) == 0 and digitalRead(right) == 0 and digitalRead(front) == 1){
myData.m =2;
} 
else if (digitalRead(left) == 1 and digitalRead(right) == 1){
myData.m =-1;
}
else if (digitalRead(left) == 0 and digitalRead(right) == 0){
myData.m =1;
}  
else if(digitalRead(front) == 1){
myData.m =0;
}

Serial.println(myData.m);
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  
  delay(300);
}