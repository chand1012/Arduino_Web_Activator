#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "CountryWifi";
const char* password = "chandnol911";

ESP8266WebServer server(80);

//String webPage = "";
String coffee1 = "";
String coffee2 = "";
int gpio0_pin = 13; // For some reason on my ESP8266 Uno board the 13th pin is actually the 11th on the board
//int gpio2_pin = 2;

void setup(void){
  //webPage += "<h1>ESP8266 Web Server</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  //webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  coffee1 += "<html><div id=\"wrapper\"><head><link rel=\"stylesheet\" href=\"https://unpkg.com/purecss@1.0.0/build/pure-min.css\" integrity=\"sha384-nn4HPE8lTHyVtfCBi5yW9d20FjT8BJwUXyWZT9InLYax14RDjBj46LmSztkmNP9w\" crossorigin=\"anonymous\"></head><link rel=\"icon\" type=\"image/png\" href=\"http://images.clipartpanda.com/coffee-clip-art-acq4B9zcM.png\" /><title> Arduino Activator</title><h1> Click Below to make Coffee!</h1> <a class=\"pure-button pure-button-primary\" href=\"/socket1On\">Make Coffee</a></div><style>#wrapper{width:1000px;margin:0 auto}</style></html>";
  coffee2 += "<html><div id=\"wrapper\"><head><link rel=\"stylesheet\" href=\"https://unpkg.com/purecss@1.0.0/build/pure-min.css\" integrity=\"sha384-nn4HPE8lTHyVtfCBi5yW9d20FjT8BJwUXyWZT9InLYax14RDjBj46LmSztkmNP9w\" crossorigin=\"anonymous\"><style>#wrapper{width:1000px;margin:0 auto}</style> <script>var CoffeeAlert=function(){alert(\"Coffee is being made!\");};</script> </head><link rel=\"icon\" type=\"image/png\" href=\"http://images.clipartpanda.com/coffee-clip-art-acq4B9zcM.png\" /><title> Arduino Activator</title><h1> Click Below to make Coffee!</h1> <a class=\"pure-button pure-button-primary\" href=\"/socket1On\">Make Coffee</a><body onload=\"CoffeeAlert();\"></body></div></html>";
  // preparing GPIOs
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  //pinMode(gpio2_pin, OUTPUT);
  //digitalWrite(gpio2_pin, LOW);

  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("");
  Serial.println("Connected to ");
  Serial.println(ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", [](){
    server.send(200, "text/html", coffee1);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", coffee2);
    digitalWrite(gpio0_pin, HIGH);
    Serial.println("Coffee Started");
    delay(1000);
    digitalWrite(gpio0_pin, LOW);
  });
  /*
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, LOW);
    delay(1000);
  });
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, HIGH);
    delay(1000);
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, LOW);
    delay(1000);
  });
  */
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
