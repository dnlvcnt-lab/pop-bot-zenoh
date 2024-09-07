#include <status/status.h>

Status::Status() {};

void Status::assignSession(z_owned_session_t session) {
    znhSession = session;
}

void Status::declarePublisher(String keyExpr) {
    topic = keyExpr;
    Serial.print("Declaring publisher for ");
    Serial.print(topic.c_str());
    Serial.println("...");
    statusPub = z_declare_publisher(z_session_loan(&znhSession), z_keyexpr(topic.c_str()), NULL);
    if (!z_publisher_check(&statusPub))
    {
        Serial.println("Unable to declare publisher.");
        while (1)
            ;
    }
}

void Status::createMsg(char *buf, size_t buf_size) {
    snprintf(buf, buf_size, "Alive!"); 
}

void Status::pubMsg() {
    char buf[50];
    createMsg(buf, sizeof(buf));
    if (z_publisher_put(z_publisher_loan(&statusPub), (const uint8_t *)buf, strlen(buf), NULL) < 0) {
        Serial.print(topic.c_str());
        Serial.println(": Error while publishing data");
    }
}