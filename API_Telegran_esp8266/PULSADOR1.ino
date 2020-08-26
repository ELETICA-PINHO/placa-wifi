void FUNCAO_PULSADOR1() {

  StatusPulsador1 = digitalRead(PULSADOR1);

  

  if (StatusPulsador1 == LOW) {
    digitalWrite(RELE1, !digitalRead(RELE1));
    Serial.println("botão pressionado 1 ");

  //  int PUL1=digitalRead(RELE1);
    


    if (digitalRead(RELE1)) {
      statusled1 = "ligado";
    } else {
      statusled1 = "Desligado";
    }


    
       String message = "RELE1 VIA PULSADOR: " + String(statusled1) + " \n";
      bot.sendMessage(chat_id, message, "Markdown");




  }
}
