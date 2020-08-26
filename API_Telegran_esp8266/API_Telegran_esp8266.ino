
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>



// Initialize Wifi connection to the router
#define WIFI_SSID "sua rede"
#define WIFI_PASSWORD "sua senha"
#define BOTtoken "seu tokem"  // Seu token do telegram




#define PULSADOR1 12
#define PULSADOR2 4
#define RELE1  16
#define RELE2 14




#define BOT_SCAN_MESSAGE_INTERVAL 1000 //Intervalo para obter novas mensagens
long lastTimeScan;  // Ultima vez que buscou mensagem
int StatusPulsador1 ; //
int StatusPulsador2 ; //
String statusled1;
String statusled2;

String text ;
String chat_id;


WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


// Trata as novas mensagens que chegaram
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
   /* String */chat_id = String(bot.messages[i].chat_id);
    /*String*/ text = bot.messages[i].text;

    // Pessoa que está enviando a mensagem
    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Convidado";

    // Tratamento para cada tipo de comando a seguir.


    if (text == "/STATUS1") {
      
      if (digitalRead(RELE1)) {
        statusled1 = "ligado";
      } else {
        statusled1 = "Desligado";
      }

      String message = "RELE1 " + String(statusled1) + " \n";
      bot.sendMessage(chat_id, message, "Markdown");

    }




    if (text == "/STATUS2") {

      if (digitalRead(RELE2)) {
        statusled2 = "ligado";
      } else {
        statusled2 = "Desligado";
      }

      String message = "RELE2 " + String(statusled2) + " \n";
      bot.sendMessage(chat_id, message, "Markdown");

    }




    if (text == "/RELE1ON") {
      digitalWrite(RELE1, HIGH);

      String message = " " + String("RELE1ON") + " \n";
      bot.sendMessage(chat_id, message, "Markdown");


    }

    if (text == "/RELE1OFF") {
      digitalWrite(RELE1, LOW);
      String message = " " + String("RELE1OFF") + " \n";
      bot.sendMessage(chat_id, message, "Markdown");
    }




    if (text == "/RELE2ON") {
      digitalWrite(RELE2, HIGH);
      String message = " " + String("RELE2ON") + " \n";
      bot.sendMessage(chat_id, message, "Markdown");
    }

    if (text == "/RELE2OFF") {
      digitalWrite(RELE2, LOW);
      String message = " " + String("RELE2OFF") + " \n";
      bot.sendMessage(chat_id, message, "Markdown");
    }



    // Cria teclado com as opções de comando
    if (text == "/OPCAO") {
      String keyboardJson = "[[\"/RELE1ON\", \"/RELE1OFF\"],[\"/RELE2ON\", \"/RELE2OFF\"],[\"/STATUS1\"],[\"/STATUS2\"],[\"/OPCAO\"]]";
      bot.sendMessageWithReplyKeyboard(chat_id, "Escolha uma das opções", "", keyboardJson, true);
    }











    // Comando de inicio de conversa no telegram
    if (text == "/start") {
      String welcome = from_name + ", bem vindo ao Bot da Eletrica Pinho.\n";
      welcome += "Para interagir com a casa, use um dos comandos a seguir.\n\n";
      welcome += "/RELE1ON   :RELE1 LIGADO\n";
      welcome += "/RELE1OFF  :RELE1 DESLIGADO\n";
      welcome += "/RELE2ON   :RELE2 LIGADO\n";
      welcome += "/RELE2OFF  :RELE2 DESLIGADO\n";
      welcome += "/STATUS1   :ESTADO RELE1\n";
      welcome += "/STATUS2   :ESTADO RELE2\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}






void setupWifi() {

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    // Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}






void setup() {

  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
  pinMode(PULSADOR1, INPUT);
  pinMode(PULSADOR1, INPUT);

  digitalWrite(RELE1, LOW);
  digitalWrite(RELE2, LOW);


  Serial.begin(115200);

  setupWifi();


  lastTimeScan = millis();
}



void loop() {


  if (millis() > lastTimeScan + BOT_SCAN_MESSAGE_INTERVAL)  {
    Serial.print("Checking messages - ");
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    Serial.println(numNewMessages);
    while (numNewMessages) {
      Serial.println("got response");

      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    lastTimeScan = millis();
  }
  yield();
  delay(30);

  FUNCAO_PULSADOR1();
  FUNCAO_PULSADOR2();



}
