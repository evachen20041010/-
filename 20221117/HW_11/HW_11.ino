#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <analogWrite.h>
#define USE_SERIAL Serial

WiFiMulti wifiMulti;
String site, county, datacreationdate, itemunit;
int pm25;
int LED_R = 16;
int LED_B = 17;
int LED_G = 4;

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_G, OUTPUT);
  USE_SERIAL.begin(115200);
  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }
  wifiMulti.addAP("WY1010", "20041010311");
}

void loop() {
  // wait for WiFi connection
  if ((wifiMulti.run() == WL_CONNECTED)) {
    HTTPClient http;
    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
    http.begin("https://data.epa.gov.tw/api/v2/aqx_p_02?api_key=e8dd42e6-9b8b-43f8-991e-b3dee723a52d&limit=1000&sort=datacreationdate%20desc&format=JSON"); //HTTP
    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        //USE_SERIAL.println(payload);
        //new
        DynamicJsonDocument doc(12288);
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
          return;
        }
        for (JsonObject field : doc["fields"].as<JsonArray>()) {
          const char* field_id = field["id"]; // "site", "county", "pm25", "datacreationdate", "itemunit"
          const char* field_type = field["type"]; // "text", "text", "text", "text", "text"
          const char* field_info_label = field["info"]["label"]; // "測站名稱", "縣市名稱", "細懸浮微粒濃度", "資料建置日期", "測項單位"
        }
        const char* resource_id = doc["resource_id"]; // "c1f31192-babd-4105-b880-a4c2e23a3276"
        const char* extras_api_key = doc["__extras"]["api_key"]; // "e8dd42e6-9b8b-43f8-991e-b3dee723a52d"
        bool include_total = doc["include_total"]; // true
        const char* total = doc["total"]; // "78"
        const char* resource_format = doc["resource_format"]; // "object"
        const char* limit = doc["limit"]; // "1000"
        const char* offset = doc["offset"]; // "0"
        const char* links_start = doc["_links"]["start"];
        const char* links_next = doc["_links"]["next"];
        for (JsonObject record : doc["records"].as<JsonArray>()) {
          const char* record_site = record["site"]; // "大城", "富貴角", "麥寮", "關山", "馬公", "金門", "馬祖", "埔里", "復興", ...
          const char* record_county = record["county"]; // "彰化縣", "新北市", "雲林縣", "臺東縣", "澎湖縣", "金門縣", "連江縣", "南投縣", ...
          const char* record_pm25 = record["pm25"]; // "14", "6", "14", "2", "12", "20", "15", "17", "28", "9", ...
          const char* record_datacreationdate = record["datacreationdate"]; // "2022-11-19 14:00", "2022-11-19 ...
          const char* record_itemunit = record["itemunit"]; // "μg/m3", "μg/m3", "μg/m3", "μg/m3", "μg/m3", ...
          if (record["site"] == "臺南") {
            site = record["site"].as<String>();
            USE_SERIAL.print("測站："); USE_SERIAL.println(site);
            county = record["county"].as<String>();
            USE_SERIAL.print("縣市："); USE_SERIAL.println(county);
            pm25 = record["pm25"].as<int>();
            USE_SERIAL.print("PM2.5："); USE_SERIAL.println(pm25);
            datacreationdate = record["datacreationdate"].as<String>();
            USE_SERIAL.print("資料建置日期："); USE_SERIAL.println(datacreationdate);
            itemunit = record["itemunit"].as<String>();
            USE_SERIAL.print("測項單位："); USE_SERIAL.println(itemunit);
          }
        }
        if (pm25 <= 500 && pm25 >= 251) {
          USE_SERIAL.println("PM2.5值251~500，紫燈");
          analogWrite(LED_R, 140);
          analogWrite(LED_G, 0);
          analogWrite(LED_B, 255);
        } else if (pm25 >= 55) {
          USE_SERIAL.println("PM2.5值55~250，紅燈");
          analogWrite(LED_R, 255);
          analogWrite(LED_G, 0);
          analogWrite(LED_B, 0);
        } else if (pm25 >= 36) {
          USE_SERIAL.println("PM2.5值36~54，橘燈");
          analogWrite(LED_R, 255);
          analogWrite(LED_G, 85);
          analogWrite(LED_B, 0);
        } else if (pm25 >= 16) {
          USE_SERIAL.println("PM2.5值16~35，黃燈");
          analogWrite(LED_R, 255);
          analogWrite(LED_G, 255);
          analogWrite(LED_B, 0);
        } else {
          USE_SERIAL.println("PM2.5值0.0~15，綠燈");
          analogWrite(LED_R, 0);
          analogWrite(LED_G, 255);
          analogWrite(LED_B, 0);
        }
      }
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
  delay(5000);
}
