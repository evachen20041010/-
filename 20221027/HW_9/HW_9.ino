#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN  5
#define RST_PIN 27
MFRC522 rfid(SS_PIN, RST_PIN);
int buzzPin = 4;
byte nuidPICC[4];
byte myidPICC1[4] = {0xDA,0xD4,0x16,0xCB};  //白卡
byte myidPICC2[4] = {0xD5,0x3A,0xCE,0x65};  //藍卡

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
  pinMode(buzzPin, OUTPUT);
  digitalWrite(buzzPin, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
}

int LED = 2;

void loop() {
  
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("RFID/NFC Tag Type: ");
      Serial.println(rfid.PICC_GetTypeName(piccType));
      // print UID in Serial Monitor in the hex format
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println();
      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
      
      if(rfid.uid.uidByte[0] == myidPICC1[0] &&
      rfid.uid.uidByte[1] == myidPICC1[1] &&
      rfid.uid.uidByte[2] == myidPICC1[2] &&
      rfid.uid.uidByte[3] == myidPICC1[3] ){
        digitalWrite(buzzPin, LOW);
        delay(100);
        digitalWrite(buzzPin, HIGH);
        delay(100);
        digitalWrite(buzzPin, LOW);
        delay(100);
        if(LED == 0){
          LED = 2;
          digitalWrite(LED_BUILTIN, LOW);
          return;
        }
        LED = 0;
        digitalWrite(LED_BUILTIN, HIGH);  //白卡恆亮
      }else if(rfid.uid.uidByte[0] == myidPICC2[0] &&
        rfid.uid.uidByte[1] == myidPICC2[1] &&
        rfid.uid.uidByte[2] == myidPICC2[2] &&
        rfid.uid.uidByte[3] == myidPICC2[3] ){
        digitalWrite(buzzPin, LOW);
        delay(100);
        digitalWrite(buzzPin, HIGH);
        delay(100);
        if(LED == 1){
          LED = 2;
          digitalWrite(LED_BUILTIN, LOW);
          return;
        }
        LED = 1;  //藍卡閃爍
      }else{
        LED = 2;
        digitalWrite(LED_BUILTIN, LOW);  //其他警報
        for(int i = 0;i < 10;i++){
          digitalWrite(buzzPin, LOW);
          delay(100);
          digitalWrite(buzzPin, HIGH);
          delay(100);
        }
      }
    }
  }
  digitalWrite(buzzPin, HIGH);
  
  if(LED == 1){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
  //Serial.print(LED);
}
