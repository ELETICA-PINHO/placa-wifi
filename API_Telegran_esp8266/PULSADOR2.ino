void FUNCAO_PULSADOR2() {

  StatusPulsador2 = digitalRead(PULSADOR2);



  if (StatusPulsador2 == LOW) {
    digitalWrite(RELE2, !digitalRead(RELE2));
    Serial.println("botão pressionado 2");

  //  int PUL2=digitalRead(RELE2);
    
 


    if (digitalRead(RELE2)) {
      statusled2 = "ligado";
    } else {
      statusled2 = "Desligado";
    }

    
       String message = "RELE2 VIA PULSADOR: " + String(statusled2) + " \n";
      bot.sendMessage(chat_id, message, "Markdown");




  }
}
