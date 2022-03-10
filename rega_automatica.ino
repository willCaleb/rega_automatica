//Usado como base para bot Telegram Programa: Bot Telegram com ESP8266 NodeMCU Autor: Arduino e Cia

#include "CTBot.h"
#include <DHTesp.h>
#include "time.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

CTBot myBot;

//Definicoes da rede wifi e conexao
String ssid  = "ALHN-ABC1"; //Nome da sua rede wifi
String pass  = "5317925704"; //Senha da sua rede wifi
String token = "5172540697:AAHXuQ--IAZkhAcAjyXR6rSxkyJtQUYxOKY"; //Token bot Telegram

//Pinos dos componentes
uint8_t rele1 = 16;

uint8_t temp = 2;

DHTesp dht;
int temperatura;
int umidade;

struct tm timeinfo;

#define ntpServer "a.st1.ntp.br"
#define NTP_OFFSET   -3*3600    // In seconds
#define NTP_INTERVAL 60*1000    // In miliseconds

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, ntpServer, NTP_OFFSET, NTP_INTERVAL);

void setup()
{
  Serial.begin(115200);
  Serial.println("Inicializando bot Telegram...");
  //Conexao na rede wifi
  myBot.wifiConnect(ssid, pass);
  //Define o token
  myBot.setTelegramToken(token);
  //Verifica a conexao
  if (myBot.testConnection())
    Serial.println("Conexao Ok!");
  else
    Serial.println("nFalha na conexao!");
  //Define os pinos dos leds como saida e apaga os leds
  pinMode(rele1, OUTPUT);
  
  digitalWrite(rele1, HIGH);
  
  dht.setup(temp, DHTesp::DHT11);
  timeClient.begin();;
  timeClient.forceUpdate();
}
void loop()
{
  //timeClient.update();
  //Variavel que armazena a mensagem recebida
  TBMessage msg;
  String tempo = timeClient.getFormattedTime();
  //Verifica se chegou alguma mensagem
  if (myBot.getNewMessage(msg))
  {
    //Verifica se foi recebia a mensagem "Clima"
    if (msg.text.equalsIgnoreCase("CLIMA"))
    {
      enviarDados(msg);
      obterHorario(msg);
    }
    else if(msg.text.equalsIgnoreCase("REGAR")){
      regar(msg);
    }
    else
    {
      //Caso receba qualquer outro comando, envia uma
      //mensagem generica/informativa
      String reply;
      reply = (String)"ATENÇÃO!!!! COMANDO INVÁLIDO!!! \n";
      reply += "COMANDOS VÁLIDOS: \n\n";
      reply += "Regar \n\n";
      reply += "Clima";
      myBot.sendMessage(msg.sender.id, reply);
    }
  }

  delay(1000);
}
