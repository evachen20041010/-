#include <WiFi.h>
#include <WiFiClientSecure.h>
//#include <SimpleDHT.h>

char SSID[] = "WY1010";
char PASSWORD[] = "20041010311";
String Linetoken = "0yOTW4szAcVRya1cLOjQmYQb5BguMMVHHGMbX41YlkO";
WiFiClientSecure client;//網路連線物件
char host[] = "notify-api.line.me";//LINE Notify API網址
int sensorPin = A0;
int sensorValue = 0;
int Data = 2, Data_old = 2;
String message;

void setup() {
  Serial.begin(115200);
  //連線到指定的WiFi SSID
  Serial.print("Connecting Wifi: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  //連線成功，顯示取得的IP
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  client.setInsecure();//ESP32核心 1.0.6以上
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if (sensorValue < 1500) {
    //天暗
    message = "天暗了!";
    Data = 0;
  } else {
    //天亮
    message = "天亮了!";
    Data = 1;
  }
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if (sensorValue < 1500 && Data_old == 0) {
    message = "天暗了!";
    Data = 0;
    Data_old == 2;
  } else if (sensorValue > 1500 && Data_old == 0) {
    message = "天亮了!";
    Data = 1;
    Data_old == 2;
  }
  if (Data_old == 2) {
    Data_old = 0;
    if (client.connect(host, 443)) {
      int LEN = message.length();
      //傳遞POST表頭
      String url = "/api/notify";
      client.println("POST " + url + " HTTP/1.1");
      client.print("Host: "); client.println(host);
      //權杖
      client.print("Authorization: Bearer "); client.println(Linetoken);
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: "); client.println( String((LEN + 8)) );
      client.println();
      client.print("message="); client.println(message);
      client.println();
      //等候回應
      delay(2000);
      String response = client.readString();
      //顯示傳遞結果
      Serial.println(response);
      client.stop(); //斷線，否則只能傳5次
    }
    else {
      //傳送失敗
      Serial.println("connected fail");
    }
  }
  //每5秒讀取一次溫濕度
  delay(5000);
}
