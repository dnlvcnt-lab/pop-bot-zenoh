#ifndef STATUS_H
#define STATUS_H

#include <Arduino.h>
#include <zenoh/zenoh_setup.h>


class Status {
    private:
        String topic;
        z_owned_session_t znhSession;
        void createMsg(char *buf, size_t buf_size);
    public:
        Status();
        z_owned_publisher_t statusPub;
        void assignSession(z_owned_session_t session);
        void declarePublisher(String zkey);
        void pubMsg();
};

#endif // STATUS_H