#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80); //Web-сервер будет работать на 80 порту

void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);
  WiFi.begin("ssid", "password");
 
  Serial.print("Connecting");  //  "Подключение:"
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
 
  Serial.print("Connected, IP address: ");
           //  "Подключились, IP-адрес: "
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", webPage());
  });
  
  server.on("/active", []() {
    digitalWrite(D4, LOW);
    server.send(200, "text/html", webPage());
  });
  
  server.on("/deactive", []() {
    digitalWrite(D4, HIGH);
    server.send(200, "text/html", webPage());
  });

  server.begin();
  Serial.println("HTTP server started");
  
}
 
void loop() {

  server.handleClient();
  
  
 }

String webPage(){
String web; 
web += "<h1> Shar170:  This site was created for demo-view server on ESP8266 <h1/>"; //заголовок
web += "<div><button> <a href=\"active\"> Off <a/></button>";
web += "<button> <a href=\"deactive\"> On <a/></button> <div/>";
return web;

}
