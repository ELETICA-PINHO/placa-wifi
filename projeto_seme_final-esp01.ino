

#include <ESP8266WiFi.h>

//Nome da sua rede Wifi
const char* ssid = "sua rede";

//Senha da rede
const char* password = "sua senha";

//IP do ESP (para voce acessar pelo browser)
IPAddress ip(192, 168, 88, 175);  // ip da sua rede wifi que fai ser atribuido esp

//IP do roteador da sua rede wifi
IPAddress gateway(192, 168, 88, 1); // gateway da sua rede wifi

//Mascara de rede da sua rede wifi
IPAddress subnet(255, 255, 255, 0);

//Criando o servidor web na porta 80
WiFiServer server(8090);

//Pino do NodeMCU que estara conectado ao rele
const int pin = 0; //Equivalente ao D2 no NodeMCU

//Funcao que sera executada apenas ao ligar o ESP8266
void setup() {
  //Preparando o pino, que esta lidago ao rele
  pinMode(pin, OUTPUT);
  digitalWrite(pin,HIGH);

  //Conectando a rede Wifi
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  
  
  //Verificando se esta conectado,
  //caso contrario, espera um pouco e verifica de novo.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //Iniciando o servidor Web
  server.begin();
}

//Funcao que sera executada indefinidamente enquanto o NodeMCU estiver ligado.
void loop() {
  //Verificando se o servidor esta pronto.
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  //Verificando se o servidor recebeu alguma requisicao
  while (!client.available()) {
    delay(1);
  }

  //Obtendo a requisicao vinda do browser
  String req = client.readStringUntil('\r');
  
  //Sugestao dada por Enrico Orlando
  if(req == "GET /favicon.ico HTTP/1.1"){
      req = client.readStringUntil('\r');
  }
  
  client.flush();

  //Iniciando o buffer que ira conter a pagina HTML que sera enviada para o browser.
  String buf = "";

  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  buf += "<head> ";
  buf += "<meta charset='UTF-8'> ";
  
  buf += "<title>ElétricaPinho</title> ";
 
  buf += "</head> ";
  buf += "<body> ";

  

  buf += "<a href='?f=on' class='btn btn-sea'>Pusador</a> ";
 
  buf += "</body> ";
  buf += "</html> ";

  //Enviando para o browser a 'pagina' criada.
  client.print(buf);
  client.flush();

  //Analisando a requisicao recebida para decidir se liga ou desliga a lampada
  if (req.indexOf("on") != -1)
  {
    digitalWrite(pin, HIGH);
    delay(1000);
    digitalWrite(pin, LOW);
  }
  
  
    //Requisicao invalida!
    client.stop();
  }
