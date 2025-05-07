#pragma once
#include "esphome.h"
#include <ESP8266WiFi.h>

class QRReaderComponent : public PollingComponent, public TextSensor {
 public:
   WiFiClient client;
   const char* host = "192.168.0.49";
   const uint16_t port = 55256;

   QRReaderComponent() : PollingComponent(1000) {}

   void setup() override {
     ESP_LOGI("QR", "Komponens inicializálása...");
   }

   void update() override {
     if (!client.connect(host, port)) {
       ESP_LOGE("QR", "TCP kapcsolódási hiba!");
       return;
     }

     String data;
     while (client.available()) {
       data += client.readStringUntil('\n');
     }
     client.stop();

     if (!data.isEmpty()) {
       publish_state(data.c_str());  // QR-kód publikálása ESPHome szenzorként
       ESP_LOGI("QR", "Beérkezett QR-kód: %s", data.c_str());
     }
   }
};
