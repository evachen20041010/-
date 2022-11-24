#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
#include <analogWrite.h>
#include <SimpleDHT.h>

const char* ssid = "WY1010";
const char* password = "20041010311";
int blink = 0,counter = 0,F = 1,G = 0;
WebServer server(80);
int pinDHT11 = 17;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
  server.on("/",handleRoot);
  server.on("/T",T);
  server.on("/H",H);
  server.begin();
}
byte temperature = 0;
byte humidity = 0;
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  // read without samples.
  
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    //Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    //Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
}

void handleRoot() {
  server.send(200, "text/plain", "5A9G0006");
}

void T() {
  server.send(200, "text/plain",(String)temperature); 
}
void H() {
  server.send(200, "text/plain", (String)humidity);
}
