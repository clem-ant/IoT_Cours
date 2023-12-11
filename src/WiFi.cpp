#include <ESP8266WiFi.h>

// CHANGE AS NEEDED
const char* ssid     = "TP-Link_5639";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "w6cPXKxB"; 
//
void get_network_info(){
  if(WiFi.status() == WL_CONNECTED){
    Serial.println((String)"[+] Informations sur le réseau pour " + ssid);
    Serial.println("[+] BSSID : " + WiFi.BSSIDstr());
    Serial.println("[+] Gateway IP :  " + WiFi.gatewayIP().toString());
    Serial.println("[+] Subnet Mask : " + WiFi.subnetMask().toString());
    Serial.println((String)"[+] RSSI : " + WiFi.RSSI() + " dB");
    Serial.println("[+] ESP32 IP : " + WiFi.localIP().toString());
    Serial.println("================================");
  }
  else{
    Serial.println("Not connected");
  }
  delay(2000);
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