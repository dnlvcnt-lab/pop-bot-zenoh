#include <Arduino.h>
#include <wifi/wifi_setup.h>
#include <zenoh/zenoh_setup.h>
#include <sensors/bumper.h>

#define MODE "peer"
#define CONNECT "udp/224.0.0.224:7446#iface=wlp0s20f3"

#define KEY_BUMPER_A "rt/popbot/bumperA"

// Zenoh Session
ZenohSession zenoh(MODE, CONNECT);

// Sensors
//// Bumper
Bumper bumperA(2); // Pin 2


void setup() {
    // Initialize Serial for debug
    Serial.begin(9600);
    while (!Serial)
    {
        delay(1000);
    }
    
    // Connect to WiFi
    connectWifi();
    delay(300);

    // Initialize Zenoh Session
    zenoh.initSession();

    // Open Zenoh Session
    zenoh.openSession();

    // Bumper Configuration
    bumperA.assignSession(zenoh.znhSession);
    bumperA.declarePublisher(KEY_BUMPER_A);
    bumperA.displayInfo();
}

void loop() {
    // Publish Bumper A
    bumperA.pubMsg();
    delay(1000);
    //Serial.println(zenoh1.ledPin);
}
