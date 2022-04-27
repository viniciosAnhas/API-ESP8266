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

  if(connectionWifi()){
      
    dht.begin();
    server.enableCORS(true); 
    restServerRouting();
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("Servico iniciado!");

  }

  else{

    Serial.print("\n Falha ao se conectar a rede \n");
    delay(3000);
    return statusConnection();

  }

}

void starService(){

  server.handleClient();

  if((millis() - timeInsertSQL) >= insertInterval){

    timeInsertSQL = millis();

    insertData();

  }

}

void insertData(){

    if (conn.connected()){

      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

      dtostrf(getHumidity(), 1, 1, hum);
      dtostrf(getTemperature(), 1, 1, temp);

      sprintf(query, INSERT_SQL, hum, temp);

      cur_mem->execute(query);
      delete cur_mem;

    }

    else{

      ESP.restart();

    }

}

bool connectionWifi(){

  Serial.printf("\nConectando a %s", ssid);

  int attempt = 1;
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){

    Serial.printf("\ntentativa: %d ª", attempt);
    attempt++;
    delay(1000);

    if(attempt >= 11){

      return false;

    }

  }

  WiFi.config(ip, subnet, gateway);

  Serial.printf("\n \nESP8266 conectado na rede %s", ssid);

  delay(2000);

  Serial.print("\nConectando no servidor SQL \n");

  if(connectSQL()){

    Serial.print("\nConectado ao servidor SQL \n");
    return true;

  }

  else{

    Serial.print("\n Falha na conexao com o servidor SQL \n");

    return connectSQL();

  }

}

bool connectSQL(){

  int attempt = 1;

  while(!conn.connect(server_addr, port, user, pass)){
    
    attempt++;
    delay(1500);

    if (attempt >= 11){

       return false;

    }

  }

  return true;

}