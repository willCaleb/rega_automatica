
void regar(TBMessage ms){
  myBot.sendMessage(ms.sender.id, "Iniciando a rega");
  digitalWrite(rele1, LOW);
  delay(3000*60);
  digitalWrite(rele1, HIGH);
  myBot.sendMessage(ms.sender.id, "Rega finalizada");
}
