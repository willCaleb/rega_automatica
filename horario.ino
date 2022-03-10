
void obterHorario(TBMessage ms) {
  String hora = "Agora são: ";
  hora += timeClient.getFormattedTime();
  String h = timeClient.getFormattedTime();
  myBot.sendMessage(ms.sender.id, h);
}
