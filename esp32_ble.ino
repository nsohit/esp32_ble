#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>
//std::stringstream mac;
const int PIN = 2;
const int CUTOFF = -60;

void setup() {
  Serial.begin(115200);
  pinMode(PIN, OUTPUT);
  BLEDevice::init("");
}

void loop() {
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  BLEScanResults results = scan->start(1);
  int best = CUTOFF;
  for (int i = 0; i < results.getCount(); i++) {
    BLEAdvertisedDevice device = results.getDevice(i);
    int rssi = device.getRSSI();
    String mac = device.getAddress().toString().c_str();
    //char nama = device.getName().toString().c_str();
    Serial.print("Device info: ");
    //Serial.print("Name: "+device.getName());
    
    Serial.print("mac address: "+mac);
    Serial.print(" RSSI: ");
    Serial.println(rssi);
    
    if (rssi > best) {
      best = rssi;
    }
  }
  digitalWrite(PIN, best > CUTOFF ? HIGH : LOW);
}
