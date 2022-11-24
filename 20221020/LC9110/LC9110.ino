#include <analogWrite.h>
int F1=21;
int F2=19; 
void setup() {
  pinMode(F1,OUTPUT);
  pinMode(F2,OUTPUT);
}

void loop() {
  for(int i=0;i<=255;i+=10){
    analogWrite(F1,i);
    delay(50);
  }
  delay(500);
  for(int i=255;i>=0;i-=10){
    analogWrite(F1,i);
    delay(50);
  }
  delay(1000);
  for(int i=0;i<=255;i+=10){
    analogWrite(F2,i);
    delay(50);
  }
  delay(500);
  for(int i=255;i>=0;i-=10){
    analogWrite(F2,i);
    delay(50);
  }
  delay(1000);
}
