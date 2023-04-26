#include <BleMouse.h>

#define pm pinMode
#define dw digitalWrite
#define dr digitalRead
#define left 21
#define right 12
#define front 23

BleMouse bleMouse("dqc", "IRForce Prime", 100);
void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleMouse.begin();
}

void loop() {
  if(bleMouse.isConnected()) {

  unsigned long startTime;
  startTime = millis();


  if (dr(left) == 1 and dr(right) == 1){
    bleMouse.move(-10,0);
  Serial.println("Scroll L");
  }
  if (dr(front) == 1){
    bleMouse.move(0,-10);

    Serial.println("Scroll U");

  }
  if (dr(left) == 0 and dr(right) == 0){
  bleMouse.move(10,0);

  Serial.println("Scroll R");
  }
  // if (dr(left) == 1 and dr(right) == 1 and dr(front) == 1){
  // myData.m = -2;
  // }
  // if (dr(left) == 0 and dr(right) == 0 and dr(front) == 1){
  // myData.m = 2;
  // }    
  }
  delay(200);
}