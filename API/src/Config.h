const char* ssid = "";
const char* password = "";

IPAddress ip(x, x, x, x);
IPAddress subnet(x, x, x, x);
IPAddress gateway(x, x, x,x1);

byte led = 2;

#define DHTPIN D4     

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

String json;

ESP8266WebServer server(80);