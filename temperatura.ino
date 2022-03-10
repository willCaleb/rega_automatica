
void enviarDados(TBMessage ms){
  
  temperatura = dht.getTemperature();
  umidade = dht.getHumidity();

  String temp = "Temperatura: ";
  String umid = "Umidade: ";
  temp += temperatura;
  umid += umidade;
  temp += "°";
  umid += "%";

  myBot.sendMessage(ms.sender.id, temp);
  myBot.sendMessage(ms.sender.id, umid);
}
