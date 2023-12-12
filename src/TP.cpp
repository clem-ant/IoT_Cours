#include <WiFi.h>
#include "BLEDevice.h"
#include <PubSubClient.h>
#include <BLEAdvertisedDevice.h>

const char *ssid = "clement";
const char *password = "rootroot";
const char *mqttBroker = "172.16.97.67";
const int mqttPort = 1883;
const char *mqttClientId = "ESP32_Client";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

BLEScan* pBLEScan;

// Variable globale pour stocker l'adresse MAC Bluetooth
String bluetoothMACAddress;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    bluetoothMACAddress = advertisedDevice.getAddress().toString().c_str();
    Serial.printf("Bluetooth MAC Address: %s\n", bluetoothMACAddress.c_str());
  }
};

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void connectToMQTT() {
  Serial.println("Connecting to MQTT...");

  mqttClient.setServer(mqttBroker, mqttPort);

  while (!mqttClient.connected()) {
    if (mqttClient.connect(mqttClientId)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.println("Failed to connect to MQTT. Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
void setup() {
  Serial.begin(115200);
  connectToWiFi();
  connectToMQTT();

  // Wait for a moment to ensure the scanning is completed
  delay(1000);

  // Publish MAC address to MQTT
  Serial.printf("Publishing MAC Address to Clement: %s\n", bluetoothMACAddress.c_str());
  mqttClient.publish("Clement", bluetoothMACAddress.c_str());

  // Wait for a moment before exiting (you can adjust as needed)
  delay(5000);
}

void loop() {
  mqttClient.publish("Clement", bluetoothMACAddress.c_str());
}
