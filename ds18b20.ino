const char* host = "api.thingspeak.com";
String url = "/update?api_key=KFSEU2UP2TMR44PP";  
const int httpPort = 80;
int interval = 60000;
float r = 0;

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D3


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);



const char* ssid = "t-broad52F5";
const char* password = "D1630B52F4";

String working() { 
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();  // Send the command to get temperatures
  Serial.println("DONE");
  Serial.print("Temperature for Device 1 is: ");
  
  r = sensors.getTempCByIndex(0);
  Serial.print(sensors.getTempCByIndex(0));
  return(String("field1=")+String(r));
}

void delivering(String payload) { 
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpPort)) {
    Serial.print("connection failed: ");
    Serial.println(payload);
    return;
  }
  String getheader = "GET "+ String(url) +"&"+ String(payload) +" HTTP/1.1";
  client.println(getheader);
  client.println("User-Agent: ESP8266 YoungHoo Park");  
  client.println("Host: " + String(host));  
  client.println("Connection: close");  
  client.println();

  Serial.println(getheader);
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }
  Serial.println("Done cycle.");
}

void connect_ap() {
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n Got WiFi, IP address: ");
  Serial.println(WiFi.localIP());  
}

void setup() {
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");   //////plus code

  sensors.begin(); ///////////////// plus code
  
  connect_ap();
}

unsigned long mark = 0;
void loop() {
  if (millis() > mark ) {
     mark = millis() + interval;
     String payload = working();
     delivering(payload);
  }
}
