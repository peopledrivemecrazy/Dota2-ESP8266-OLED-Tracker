#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include "SSD1306.h"


ESP8266WebServer server(80);
SSD1306  display(0x3c, D3, D4);

const char* ssid = "Your WIFI";
const char* password = "Your WIFI Password";
String api = "Your API";
String leagueid = "9870";
String url = "http://api.steampowered.com/IEconDOTA2_570/GetTournamentPrizePool/v1/?key="+api+"&leagueid="+leagueid;
String json;
long prize, base = 1600000, moneyspent;
unsigned long previousMillis = 0;
const long interval = 5000;

void getdata() {
  HTTPClient http;
  Serial.println(url);
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    json = http.getString();
    Serial.println(json);
  }
  http.end();
}
void parsejson() {
  getdata();
  const size_t bufferSize = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + 60;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& root = jsonBuffer.parseObject(json);
  JsonObject& result = root["result"];
  prize = result["prize_pool"];
  moneyspent = prize - base;
  Serial.println(prize);
  Serial.println(moneyspent);
  showdata();
}
void showdata() {
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "TI8 Total Prize Pool");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 12, "$ " + String(prize));
   display.setFont(ArialMT_Plain_10);
  display.drawString(0, 32, "Community contribution");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 48, "$ " + String(moneyspent));
  display.display();
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Initializing TI8");
    display.setFont(ArialMT_Plain_16);
  display.drawString(0, 14, "tracker");
  display.display();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()  {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    parsejson();
  }
  server.handleClient();

}
