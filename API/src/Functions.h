float getHumidity(){

  return dht.readHumidity();

}

float getTemperature(){

  return dht.readTemperature();

}

void getSensor() {

    json = "{";
 
    json+= "\"Humi\": \""+ String(getHumidity()) +"\"";
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

  if(connection()){
      
    dht.begin();
    server.enableCORS(true); 
    restServerRouting();
    server.onNotFound(handleNotFound);
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

  Serial.printf("Conectando a %s", ssid);

  int attempt = 1;
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){

    Serial.printf("\n tentativa: %d", attempt);
    attempt++;
    delay(1000);

    if(attempt >= 11){

      return false;

    }

  }

  WiFi.config(ip, subnet, gateway);

  Serial.printf("\nESP8266 conectado na rede %s", ssid);

  delay(1500);

  Serial.println("");
  Serial.println("Conectando no servidor SQL");

  if(connectSQL()){

    Serial.println("Conexao SQL OK!!!");
    digitalWrite(led, LOW);
    return true;

  }

  else{

    Serial.println("Falha na conexao SQL");

    return connectSQL();

  }

}

bool connectSQL(){

  int attemptSQL = 1;

  while(!conn.connect(server_addr, port, user, pass)){
    
    attemptSQL++;
    delay(1500);

    if (attemptSQL >= 11){

       return false;

    }


  }

  return true;

}