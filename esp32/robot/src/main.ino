#include <Arduino.h>
#include <wifi/wifi_setup.h>
#include <zenoh/zenoh_setup.h>
#include <status/status.h>
#include <sensors/bumper.h>

#define MODE "peer"
#define CONNECT "udp/224.0.0.224:7447#iface=wlp0s20f3"

#define KEY_STATUS "rt/popbot/status"
#define KEY_BUMPER_A "rt/popbot/bumperA"

// Zenoh Session
ZenohSession zenoh(MODE, CONNECT);

// Status
Status robotStatus;

// Sensors

/* Bumper
    - ID:   A
    - Pin:  2   
*/
Bumper bumperA(2);


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

    // Status Configuration
    robotStatus.assignSession(zenoh.znhSession);
    robotStatus.declarePublisher(KEY_STATUS);

    // Bumper Configuration
    bumperA.assignSession(zenoh.znhSession);
    bumperA.declarePublisher(KEY_BUMPER_A);
    bumperA.displayInfo();
}

void loop() {
    // Status
    robotStatus.pubMsg();
    delay(5000);

    // Publish Bumper A
    //bumperA.pubMsg();
    //delay(2000);

}
