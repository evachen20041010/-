#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include <analogWrite.h>

const char* ssid = "WY1010";
const char* password = "20041010311";
int blink = 0,counter = 0,F = 1,G = 0;
WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
  server.on("/",handleRoot);
  server.on("/Hello",hello);
  server.on("/ON",On);
  server.on("/OFF",Off);
  server.on("/FLASH",flash);
  server.on("/FAST",fast);
  server.on("/BREATH",breath);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

  int Blink;
  counter += 1;
  if(G == 1){
    Blink = 500;
  }else if(G == 2){
    Blink = 100;
  }else if(G == 3){
    digitalWrite(LED_BUILTIN, LOW);
    for(int i = 0;i > 256;i++){
      analogWrite(LED_BUILTIN, i);
      delay(10);
    }
    for(int i = 255;i >= 0;i--){
      analogWrite(LED_BUILTIN, i);
      delay(10);
    }
  }
  if(counter > Blink){
    if(blink == 1 && F == 1){
      digitalWrite(LED_BUILTIN, HIGH);
      F = -F;
    }else if(blink == 1 && F == -1){
      digitalWrite(LED_BUILTIN, LOW);
      F = -F;
    }
    counter = 0;
  }
}

void handleRoot() {
  server.send(200, "text/plain", "Eva Chen\n5A9G0006");
}

void hello() {
  server.send(200, "text/plain", "Hello");
}

void On() {
  digitalWrite(LED_BUILTIN, HIGH);
  blink = 0;
  server.send(200, "text/plain", "On");
}

void Off() {
  digitalWrite(LED_BUILTIN, LOW);
  blink = 0;
  server.send(200, "text/plain", "Off");
}

void flash() {
  blink = 1;
  G = 1;
  server.send(200, "text/plain", "flash");
}

void fast() {
  blink = 1;
  G = 2;
  counter = 0;
  server.send(200, "text/plain", "fast");
}

void breath() {
  blink = 1;
  G = 3;
  server.send(200, "text/plain", "breath");
}
