#include <Arduino.h>
#include "wifi_setup.h"

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing...");
    connect_wifi();
}

void loop() {
    Serial.println("Loop");
    delay(1000);
}
