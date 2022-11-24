int buzzPin = 4;
void setup() {
  pinMode(buzzPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i=0;i<6;i++){
      digitalWrite(buzzPin, LOW);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(buzzPin, HIGH);                       
      digitalWrite(LED_BUILTIN, LOW);   
      delay(500);
  }
  
}

void loop() {
    
    
}
