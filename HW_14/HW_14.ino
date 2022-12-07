#include <WiFi.h>
#include <PubSubClient.h>
#include <ctime>

const char* ssid = "TP-LINK_6F46";
const char* password = "aa3632aa";
const char* mqttServer = "192.168.0.104";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  Serial.println("連線成功");

  client.setServer(mqttServer, mqttPort);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {

  srand(time(NULL));
  int tmp = rand() % 61 - 10;
  int hum = rand() % 71 + 20;
  char msg[64] = { 0 };

  strcat(msg, String(tmp).c_str());
  strcat(msg, ",");
  strcat(msg, String(hum).c_str());

  client.publish("HW_14", msg);

  delay(1000);

  client.loop();
}
