#include <WiFi.h>

const char *ssid = "AP_CYBERIOT";
const char *password = "password";

void setup() {
    Serial.begin(115200);

    WiFi.softAP (ssid, password);
    // Configuration de la plage d'adresses IP pour le DH 
    IPAddress local_IP (192, 168, 50, 1); 
    IPAddress gateway (192, 168, 50, 1); 
    IPAddress subnet (255, 255, 255, 0); 
    WiFi.softAPConfig (local_IP, gateway, subnet);

    Serial.println("Point d'accès démarré");
    Serial.print("IP : ");
    Serial.println(WiFi.softAPIP());
}

void loop() {
    Serial.print("IP : ");
    Serial.println(WiFi.softAPIP());
}