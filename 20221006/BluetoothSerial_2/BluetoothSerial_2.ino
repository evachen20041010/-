#include <BluetoothSerial.h>
BluetoothSerial BT;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  BT.begin("5A9G0006");
}

char Data;

void loop() {
  if(BT.available() > 0){
    Data = BT.read();
    Serial.println(Data); 
    if(Data == '1'){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
    }else if(Data == '2'){
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    } 
  }
  delay(500);
}  
