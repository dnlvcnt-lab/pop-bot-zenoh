#include <sensors/bumper.h>

Bumper::Bumper(int pin) {
    sensorPin = pin;
}

void Bumper::readSensor() {
    sensorState = digitalRead(sensorPin) == HIGH;
}

void Bumper::displayInfo() {
    Serial.println("Sensor: ");
    Serial.print("--- topic: ");
    Serial.println(topic);
    Serial.print("--- pin:   ");
    Serial.println(sensorPin);
}

int Bumper::getState() {
    return sensorState;
}

void Bumper::assignSession(z_owned_session_t session) {
    znhSession = session;
}

void Bumper::declarePublisher(String keyExpr) {
    topic = keyExpr;
    Serial.print("Declaring publisher for ");
    Serial.print(topic);
    Serial.println("...");
    sensorPub = z_declare_publisher(z_session_loan(&znhSession), z_keyexpr(topic.c_str()), NULL);
    if (!z_publisher_check(&sensorPub))
    {
        Serial.println("Unable to declare publisher for key expression!\n");
        Serial.println(topic);
        while (1)
            ;
    }
}

void Bumper::createMsg(char *buf) {
    sensorMeasure.data = getState();
    serializeBoolMsg(&sensorMeasure, buf);
}

void Bumper::pubMsg() {
    //uint8_t bool_serialized_size = 4 + sizeof(int);
    char buf[boolSerializedSize];
    createMsg(buf);
    if (z_publisher_put(z_publisher_loan(&sensorPub), (const uint8_t *)buf, boolSerializedSize, NULL) < 0) {
        Serial.println("Error while publishing data");
    } else {
        Serial.print("PUB OK: ");
        Serial.println(getState());
    }
}