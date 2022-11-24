#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include <analogWrite.h>

const char* ssid = "";  //名稱
const char* password = ""; //密碼
WebServer server(80);
int M=0;
const int IA = 17;  //順
const int IB = 16;  //反

void setup() {
  // put your setup code here, to run once:
  pinMode(IA,OUTPUT);
  pinMode(IB,OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
  server.on("/",handleRoot);
  server.on("/FON",fon);
  server.on("/BON",bon);
  server.on("/OFF",off);
  server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  if(M == 1){
    analogWrite(IA,150);
    analogWrite(IB,0);
  }else if(M == 2){
    analogWrite(IA,0);
    analogWrite(IB,150);
  }else if(M == 3){
    analogWrite(IA,0);
    analogWrite(IB,0);
  }
}

void handleRoot() {
  server.send(200, "text/plain", "5A9G0018");
}

void fon() {
  server.send(200, "text/plain","FON");
  M = 1;
}
void bon() {
  server.send(200, "text/plain","BON");
  M = 2;
}
void off() {
  server.send(200, "text/plain","OFF");
  M = 3;
}
