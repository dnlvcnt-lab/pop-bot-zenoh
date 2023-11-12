#include <zenoh/zenoh_setup.h>


ZenohSession::ZenohSession(String mode, String connect) {
    znhMode = mode;
    znhConnect = connect;
}

void ZenohSession::initSession() {
    Serial.println("Initializing Zenoh Session...");
    znhConfig = z_config_default();
    zp_config_insert(z_config_loan(&znhConfig), Z_CONFIG_MODE_KEY, z_string_make(znhMode.c_str()));
    if (strcmp(znhConnect.c_str(), "") != 0)
    {
        zp_config_insert(z_config_loan(&znhConfig), Z_CONFIG_CONNECT_KEY, z_string_make(znhConnect.c_str()));
    }
}

void ZenohSession::openSession() {
    Serial.println("Opening Zenoh Session...");
    znhSession = z_open(z_config_move(&znhConfig));
    if (!z_session_check(&znhSession))
    {
        Serial.println("Unable to open session!\n");
        while (1)
            ;
    }
    Serial.println("OK!");

    // Start the receive and the session lease loop for zenoh-pico
    zp_start_read_task(z_session_loan(&znhSession), NULL);
    zp_start_lease_task(z_session_loan(&znhSession), NULL);
}
