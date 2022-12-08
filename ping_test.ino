#include <FastLED.h>
#include <WiFi.h>
#include <ESP32Ping.h>

const char* ssid = "R7000";
const char* password =  "19850514";
const char* monitoring_ip = "192.168.1.35";

#define NUM_LEDS 1

#define DATA_PIN 5
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed

    WiFi.begin(ssid, password);
   
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi...");
    }
}

void loop() {
  bool success = Ping.ping(monitoring_ip, 3);
 
  if(success){
    leds[0] = CRGB::Green;
    Serial.println("Ping ok");
  }
  else{
    leds[0] = CRGB::Red;
    Serial.println("Ping failed");
  }
  FastLED.show();
}
