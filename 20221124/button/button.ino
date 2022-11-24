int button = 21;

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  Serial.begin(115200);
}

int Data = 1, old = 1, counter = 0;

void loop() {
  // put your main code here, to run repeatedly:
  Data = digitalRead(button);
  Serial.println(counter);
  if(Data == 0 && old == 1){
    counter = (counter + 1) % 77;  
  }
  old = Data;
  delay(50);
}
