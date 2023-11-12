#include <tools/serializer.h>

/* --- Serialize Functions --- */
char *serializeIntAsLittleEndian(int val, char *buf) {
    int *c_val = &val;
    for (int i = 0; i < sizeof(int); ++i, ++buf)
    {
        *buf = 0xFF & (*c_val >> (i * 8));
    }
    return buf;
}

char *serializeBool(int data, char *buf) {
    buf = serializeIntAsLittleEndian(data, buf);
    return buf;
}

char *serializeBoolMsg(BoolMsg *msg, char *buf) {
    // Serialize BoolMsg header for little endian
    *(buf++) = 0x00;
    *(buf++) = 0x01;
    *(buf++) = 0x00;
    *(buf++) = 0x00;
    buf = serializeBool(msg->data, buf);

    return buf;
}

/* --- Print Functions --- */
void printBool(struct BoolMsg *d) {
    Serial.print("Data: ");
    Serial.print(d->data);
}