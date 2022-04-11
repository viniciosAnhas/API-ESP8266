#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

const char* ssid = "";
const char* password = "";

IPAddress ip(x, x, x, x);
IPAddress subnet(x, x, x, x);
IPAddress gateway(x, x, x, x); 

byte led = 2;

#define DHTPIN 3     

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

String json;

ESP8266WebServer server(80);

bool connection();
void statusConnection();
void getSensor();
void restServerRouting();
void handleNotFound();
float getHumidity();
float getTemperature();

void setup(){

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  delay(1000);
  digitalWrite(led, HIGH);
  Serial.println("");

  WiFi.mode(WIFI_STA);

  statusConnection();
  dht.begin();
  server.enableCORS(true); 
  restServerRouting();
  server.onNotFound(handleNotFound);

  server.begin();

    Serial.print("Humi: ");
    Serial.print(getHumidity());
    Serial.print(" Temp:");
    Serial.println(getTemperature());

  delay(1000);

}

void loop(){

  server.handleClient();

}

float getHumidity(){

  return dht.readHumidity();

}

float getTemperature(){

  return dht.readTemperature();

}

void getSensor() {

    json = "{";
 
    json+= "\"Humi:\": \""+ String(getHumidity()) +"\"";
    json+= ",\"Temp\": \""+ String(getTemperature()) +"\"";
 
    json+="}";

    server.send(200, "text/json", json);

}

void restServerRouting() {
    server.on("/", HTTP_GET, []() {
        server.send(200, F("text/html"),
            F("<h1>It's ESP8266</h1>"));
    });
    server.on(F("/sensor"), HTTP_GET, getSensor);
}
 
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void statusConnection(){

  bool status =  connection();

  if(status){

    Serial.println("");
    Serial.print("Conectado a rede sem fio, ");
    Serial.println(ssid); 
    server.begin();
    Serial.println("Servico iniciado!");

  }

  else{

    Serial.println("Algo esta errado!!!");
    delay(1000);
    return setup();

  }

}

bool connection(){

  Serial.print("Conectando a ");
  Serial.print(ssid);

  int attempt = 1;
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){

    Serial.println("");
    Serial.print("tentativa: ");
    Serial.print(attempt);
    attempt++;
    delay(1000);

    if(attempt >= 11){

      Serial.println("");
      return false;

    }

  }

  WiFi.config(ip, subnet, gateway);

  digitalWrite(led, LOW);
  return true;

}