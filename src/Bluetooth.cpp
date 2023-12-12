#include "BLEDevice.h"
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEServer.h>
#include <Arduino.h>


int scanTime = 20;  // En secondesa
BLEScan* pBLEScan;

// Class recevant les résultats du scan et les traites
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.printf("Dispositif reconnu : %s \n", advertisedDevice.toString().c_str() );
    // Serial.printf("Nom du dispositif : %s \n", advertisedDevice.getName().c_str());
    Serial.printf("Adresse Mac du dispositif : %s \n", advertisedDevice.getAddress().toString().c_str());
    // Serial.printf("Donnees fabricant : %s \n", advertisedDevice.getManufacturerData().c_str());
    Serial.printf("Signal Rssi : %d \n", advertisedDevice.getRSSI());
  }
};
void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");
  BLEDevice::init("");
  // créer un nouveau scan
  pBLEScan = BLEDevice::getScan();

  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  // le balayage actif consomme plus d'énergie,
  //mais permet d'obtenir des résultats plus rapidement
  pBLEScan->setActiveScan(true);
  // Définissez l'intervalle de balayage (Msecs).
  pBLEScan->setInterval(100);
  // Configurez la fenêtre pour qu'elle effectue un balayage actif (Msecs).
  pBLEScan->setWindow(99);
}


void loop() {
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  //supprimer les résultats du tamponBLEScan pour libérer de la mémoire
  pBLEScan->clearResults();
  delay(20000);
}