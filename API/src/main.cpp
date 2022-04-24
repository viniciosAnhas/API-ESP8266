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
  pinMode(led, OUTPUT);

  delay(1000);
  
  digitalWrite(led, HIGH);
  Serial.println("");

  WiFi.mode(WIFI_STA);

  statusConnection();



  delay(1000);

}

void loop(){

  server.handleClient();

  if((millis() - timeInsertSQL) >= 300000){

    timeInsertSQL = millis();

    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

    dtostrf(getHumidity(), 1, 1, hum);
    dtostrf(getTemperature(), 1, 1, temp);

    sprintf(query, INSERT_SQL, hum, temp);

    cur_mem->execute(query);
    delete cur_mem;

  }

}