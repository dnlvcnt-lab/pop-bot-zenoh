#ifndef ZENOH_SETUP_H
#define ZENOH_SETUP_H

#include <Arduino.h>

extern "C"
{
#include "zenoh-pico.h"
}


class ZenohSession {
    private:
        String znhMode;
        String znhConnect;
        z_owned_config_t znhConfig;
        
    public:
        z_owned_session_t znhSession;
        ZenohSession(String mode, String connect); 
        void initSession();
        void openSession();

};

#endif // ZENOH_SETUP_H
