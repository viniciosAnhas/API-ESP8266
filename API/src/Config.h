const char* ssid = "";
const char* password = "";

IPAddress ip(x, x, x, x);
IPAddress subnet(x, x, x, x);
IPAddress gateway(x, x, x, x);

char name[] = "lolin";

IPAddress serverSQL(x, x, x, x); 
#define port 3306
char user[] = "";
char pass[] = "";
char INSERT_SQL[] = "INSERT INTO dbesp8266.dht11 (humi, temp, day_register, hour_register) VALUES (%s, %s, CURDATE(), CURTIME())";
char query[255];

#define DHTPIN D4

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

String json;

ESP8266WebServer server(80);

WiFiClient client;

MySQL_Connection conn((Client *)&client);
char temp[100];
char hum[100];

unsigned long timeInsertSQL = 0;
unsigned long insertInterval = 300000;