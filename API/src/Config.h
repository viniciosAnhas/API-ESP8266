const char* ssid = "Beco Diagonal";
const char* password = "c@t!7rkvl9";

IPAddress ip(192, 168, 15, 200);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 15, 1);

byte led = 2;

#define DHTPIN D4     

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

String json;

ESP8266WebServer server(80);