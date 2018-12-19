#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <MQ2.h>

int mq = A0;
MQ2 mq2(mq);

ESP8266WebServer server(80);

float sensorValue;
float sensor_volt;

    
void handleRoot() {


    sensorValue = analogRead(A0);
    sensor_volt = sensorValue/1024*5.0;
    
  
  server.send(200, "application/json", "{\r\n\r\"data\":\""+String(sensor_volt)+"\"\r\n\r}");
}


#ifndef STASSID
#define STASSID "WifiM2M"
#define STAPSK  "0wifim2m"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }



  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

}
