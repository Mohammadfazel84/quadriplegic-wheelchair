/*
RECIEVE
*/

#include <esp_now.h>
#include <WiFi.h>
#include "BluetoothSerial.h" 

#define ml1 5
#define ml2 18
#define mr1 19
#define mr2 21
#define temp 33
#define light 32
#define sharp 26
#define buzer 23
#define ms1 25
#define ms2 27
#define heater 17
#define fan 16
#define LED 22

BluetoothSerial ESP_BT; 

int incoming;

int x1;

void motor(int jahat)
{
  // forward
  if(jahat==0)
  {
    digitalWrite(ml1,HIGH);
    digitalWrite(ml2,LOW);
    digitalWrite(mr1,HIGH);
    digitalWrite(mr2,LOW);
  }
//backward  
  if(jahat==6)
  {
    digitalWrite(ml1,LOW);
    digitalWrite(ml2,HIGH);
    digitalWrite(mr1,LOW);
    digitalWrite(mr2,HIGH);
  }
//   right
  else if(jahat == 1)
  {   
    digitalWrite(ml1,HIGH);
    digitalWrite(ml2,LOW);
    digitalWrite(mr1,LOW);
    digitalWrite(mr2,LOW);
  }
  // left
  else if(jahat == -1)
  {
    digitalWrite(ml1,LOW);
    digitalWrite(ml2,LOW);
    digitalWrite(mr1,HIGH);
    digitalWrite(mr2,LOW);    
  }
  // s
  else if(jahat == 5)
  {
    digitalWrite(ml1,LOW);
    digitalWrite(ml2,LOW);
    digitalWrite(mr1,LOW);
    digitalWrite(mr2,LOW); 
  }
}



// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int m;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
if(ms1 == 0){if (myData.m != 5){
  Serial.println(myData.m);
  motor(myData.m);
  delay(500);
  }}

// Serial.print("sharp   ");
// Serial.println(analogRead(sharp));

// Serial.print("temp   ");
// Serial.println(analogRead(temp));

// Serial.print("light   ");
// Serial.println(analogRead(light));

// Serial.print("ms1   ");
// Serial.println(digitalRead(ms1));

// Serial.print("ms2   ");
// Serial.println(digitalRead(ms2));
// Serial.print("esp now   ");
// Serial.println(myData.m);
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(ml1,OUTPUT);
pinMode(ml2,OUTPUT);
pinMode(mr1,OUTPUT);
pinMode(mr2,OUTPUT);
pinMode(buzer,OUTPUT);
pinMode(LED,OUTPUT);
pinMode(heater,OUTPUT);
pinMode(fan,OUTPUT);

pinMode(temp,INPUT);
pinMode(light,INPUT);
pinMode(sharp,INPUT);
pinMode(ms1,INPUT);
pinMode(ms2,INPUT);

  ESP_BT.begin("Quadriplegic app"); //Name of your Bluetooth interface -> will show up on your phone


  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  if(ms1 == 0){
  if(digitalRead(ms2) == 0){
x1 ++;
  }
  if((x1 % 2)==0){
  if(analogRead(sharp) > 450)  {
    digitalWrite(buzer, HIGH);
  }
  else{
    digitalWrite(buzer, LOW);
  }
  if(analogRead(temp) > 1200){
    digitalWrite(fan, HIGH);
  }
  else{
    digitalWrite(fan, LOW);    
  }
  if(analogRead(temp) < 1200){
    digitalWrite(heater, HIGH);
  }
  else{
        digitalWrite(heater, LOW);

  }
  if(analogRead(light) > 3000){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
  }
if ((x1 % 2) == 1){


}
  if (ESP_BT.available()) {
    incoming = ESP_BT.read(); //Read what we receive 

    // separate button ID from button value -> button ID is 10, 20, 30, etc, value is 1 or 0
    int button = floor(incoming / 10);
    int value = incoming % 10;

    switch (button) {
      case 1:  
        digitalWrite(fan, value);
        break;
      case 2:  
        digitalWrite(heater, value);
        break;
    }
  }
  }
}  
}