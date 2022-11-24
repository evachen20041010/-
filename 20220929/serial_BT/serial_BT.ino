#include <BluetoothSerial.h>
BluetoothSerial BT;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  BT.begin("66666");
}

char Data,old_Data;
int D,old_D;
void loop() {
  D = BT.available();
  if(D > 1){
    Data = BT.read();
    BT.print("我收到：");
    BT.println(Data);  
    old_Data = Data;
    return;
  }else{
  }
  if(old_Data == '1'){
    digitalWrite(LED_BUILTIN,HIGH); 
  }else if(old_Data == '2'){
    digitalWrite(LED_BUILTIN,LOW);
  }else if(old_Data == '3'){
    digitalWrite(LED_BUILTIN,HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN,LOW);
    delay(500);
  }
  delay(500);
}
