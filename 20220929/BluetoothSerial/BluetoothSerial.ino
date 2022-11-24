#include <BluetoothSerial.h>
BluetoothSerial BT;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);
  BT.begin("66666");
}

char Data;
int flash = 0,led = 1;

void loop() {
  // put your main code here, to run repeatedly:
  BT.println("Hi!piyan");
  delay(500);
}
