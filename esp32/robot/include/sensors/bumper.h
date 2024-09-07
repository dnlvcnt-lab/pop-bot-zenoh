#ifndef BUMPER_H
#define BUMPER_H

#include <Arduino.h>
#include <zenoh/zenoh_setup.h>
#include <tools/serializer.h>
#include <msgs/bool_msg.h>


class Bumper {
    private:
        uint8_t sensorPin;
        int sensorState;
        String topic;
        BoolMsg sensorMeasure;
        z_owned_session_t znhSession;
        void createMsg(char *buf);
        void readSensor();
        
    public:
        Bumper(uint8_t pin);
        z_owned_publisher_t sensorPub;
        void displayInfo();
        int getState();
        void assignSession(z_owned_session_t session);
        void declarePublisher(String zkey);
        void pubMsg();
};

#endif // BUMPER_H
