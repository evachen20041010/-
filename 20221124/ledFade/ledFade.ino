#include <Arduino.h>
#include <analogWrite.h>

int LED_R = 16;
int LED_B = 17;
int LED_G = 4;

void setup() {
  // Set resolution for a specific pin
  pinMode(LED_R,OUTPUT);
  pinMode(LED_B,OUTPUT);
  pinMode(LED_G,OUTPUT);
}

void loop() {
  
  analogWrite(LED_R, 83);
  analogWrite(LED_B, 109);
  analogWrite(LED_G, 79);

  delay(10);
}
