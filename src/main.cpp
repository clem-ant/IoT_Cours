#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid     = "TP-Link_5639";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "w6cPXKxB"; 
// put function declarations here:
int myFunction(int, int);

void get_network_info(){
  if(WiFi.status() == WL_CONNECTED){
    Serial.print("[+] Informations sur le réseau pour ");
    Serial.println(ssid);

    Serial.println("[+] BSSID : " + WiFi.BSSIDstr());
    Serial.print("[+] Gateway IP :  ");
    Serial.println(WiFi.gatewayIP());
  }
  else{
    Serial.println("Not connected");
  }
}
void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
 get_network_info();
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}