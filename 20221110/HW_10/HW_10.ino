#include <WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = "WY1010";   // your network SSID (name)
char pass[] = "20041010311";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
unsigned long myChannelNumber = 1929332;
const char * myWriteAPIKey = "B6JDRXKHR26NLO0V";
int z[2];

void setup() {
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if (Serial.available() > 1) {
    z[0] = Serial.parseInt();
    z[1] = Serial.parseInt();
    ThingSpeak.setField(1, z[0]);
    ThingSpeak.setField(2, z[1]);
    Serial.println(z[0]);
    Serial.println(z[1]);
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if (x == 200) {
      Serial.println("Channel update successful.");
    }
    else {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
  }
  delay(20000); // Wait 20 seconds to update the channel again
}
