#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <Config.h>
#include <Declaration.h>
#include <Functions.h>

void setup(){

  Serial.begin(9600);

  delay(1000);
  
  WiFi.mode(WIFI_STA);

  statusConnection();

  delay(1000);

}

void loop(){

  starService();

}