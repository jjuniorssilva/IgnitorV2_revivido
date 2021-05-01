void notifyClients(String response) { // essa função é recebe e transmite o feedback para o cliente socket
  ws.textAll(response);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) { // essa função recebe a aquisição do cliente e analisa seu significado;
  
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
     if (strcmp((char*)data, "IG=1") == 0){
      iniciar_ignicao(true,(char*)data);
     }else if (strcmp((char*)data, "IG=0") == 0){
      iniciar_ignicao(false,(char*)data);
     }else if (strcmp((char*)data, "CARG=1") == 0){
      iniciar_carga(true,(char*)data);
     }else if (strcmp((char*)data, "CARG=0") == 0){
      iniciar_carga(false,(char*)data);
     }else if (strcmp((char*)data, "DES=1") == 0){
      iniciar_descarga(true,(char*)data);
      notifyClients(String((char*)data));
     }else if (strcmp((char*)data, "DES=0") == 0){
      iniciar_descarga(false,(char*)data);
     }else if (strcmp((char*)data, "CNX") == 0){
      notifyClients(String((char*)data));
     }
     delay(10);
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,void *arg, uint8_t *data, size_t len) { // função padrão do websocket para verificar o staus dos canais
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void initWebSocket() { // função de inicialização do protoco websocket
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}
