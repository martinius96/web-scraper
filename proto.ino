
#include <ESP8266WiFi.h> //kniznica pre ESP8266 dosku - pre wifi
#include <WiFiClientSecure.h> //KNIZNICA pre HTTPS spojenia
#include <ESP8266HTTPClient.h>
const char * ssid = "Martinko"; //meno wifi siete
const char * password = "chefrolet"; //Heslo na wifi siet
const char * host = "www.kupsito.sk"; //bez https a www
const int httpsPort = 443; //https port pre prenos
const char* fingerprint = "‎‎b9 85 17 a6 5c 08 59 ff 8f 13 96 c9 5d a9 f8 a9 93 af 5a 11";
String inData;
void setup() {
Serial.begin(500000); //rychlost seriovej linky
  Serial.println();
    IPAddress ip(192, 168, 2, 50); // where xx is the desired IP Address
IPAddress gateway(192, 168, 2, 20); // set gateway to match your network
Serial.print(F("Setting static ip to : "));
Serial.println(ip);
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your
WiFi.config(ip, gateway, subnet);
  Serial.println("pripajam na ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //pripoj sa na wifi siet s heslom
  while (WiFi.status() != WL_CONNECTED) { //pokial sa nepripojime na wifi opakuj pripajanie a spustaj funkcie pre ovladanie v offline rezime
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi pripojene"); //uspesne pripojenie na wifi siet
  Serial.println("IP adresa: ");
  Serial.println(WiFi.localIP()); // pridelena IP adresa pre dosku
  index();
}
void index() {
  WiFiClientSecure client; //HTTPS client
  if (client.verify(fingerprint, host)) {} else {}
  if (client.connect(host, httpsPort)) {
    Serial.println("Connected to server!");
   String url = "/";
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: NodeMCU\r\n" + "Connection: close\r\n\r\n");

   
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
       char thisChar = client.read();
      inData += thisChar; 



// echo to the server what's been received to confirm we have the string
if (thisChar == '\n')
        {
          Serial.print("\nreceived:");
          Serial.print(inData);
            HTTPClient http;
http.begin("http://www.arduino.php5.sk/connect.php");
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
http.POST("c="+inData);
http.writeToStream(&Serial);
http.end();
              inData = "";          
      }

  
    }
    client.stop();
  }
}
void loop() {

}
