#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include "index.h"
LiquidCrystal_I2C lcd(0x3F, 20, 4);

const char* ssid = "Dayane";
const char* password = "92378687";

const int pin_ig = D4;
const int pin_carga = D1;
const int pin_bateria = D7;
const int pin_bottao_ig = D5;
const int pin_bottao_carga = D8;
const int chipSelect = D8;// SD CARD
//const int  ADDO = D6    //Data Out
//const int  ADSK = D7    //SCK

bool contagem = false, carga=false, descarga=false;
int time_cont=10,bateria=0, cap_carga=90;
unsigned long time_atual = 0, aux_contagem=0,aux_cont_update=0,empuxo=0;

// Cria o objeto AsyncWebServer na porta  80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");


void setup(){
  Serial.begin(115200);
  pinMode(pin_bottao_ig, INPUT_PULLUP);
  pinMode(pin_bottao_carga, INPUT_PULLUP); // Se comportar como pull_down
  pinMode(pin_ig, OUTPUT);
  //pinMode(ADDO, INPUT_PULLUP);   //entrada para receber os dados
  //pinMode(ADSK, OUTPUT);         //saída para SCK
  // interrupções dos botoes
  attachInterrupt(digitalPinToInterrupt(pin_bottao_ig), attach_ig, FALLING); 
  attachInterrupt(digitalPinToInterrupt(pin_bottao_carga), attach_carga, CHANGE); 
  // initialize the lcd
  lcd.init();                     
  lcd.backlight();
  // conexão com a rede
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Aguardando a rede...");
    lcd.setCursor(0, 0);
    lcd.print("Aguardando a rede...");
    lcd.clear();
  }
  initWebSocket();
  // Rota para quando acessar o ip retornar a pagina index.h
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  // Iniciar o servidor
  server.begin();
  // Exibir para o usuario o ip a ser acessado
  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 1);
  lcd.print("Acesse:"+WiFi.localIP());
  delay(2000);
  updateDisplayData(); // apos wxibir o ip por 2s, inicializa a interface de exibição
}

void loop() {
  long time_atual = millis(); // coleta do tempo atual em relação ao inicio do micro em milissegundos
  ws.cleanupClients(); // Garante que quando o numero de conexões(canais) chegar perto do limite, os mais antigos serão desconectados 
  cont_reg(time_atual);// contagem regressiva
  //coletarDados(); // aloca os dados na variaveis globais 
  updateIntefaceData(time_atual); // Atualiza a inteface remota com os dados coletados
  updateDisplayData();// Atualiza a inteface local com os dados coletados
  //armazenarDados(time_atual); // Armazena os dados no sd
}
