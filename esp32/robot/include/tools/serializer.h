#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <Arduino.h>
#include <msgs/bool_msg.h>

uint8_t boolSerializedSize = 4 + sizeof(int);

char *serializeIntAsLittleEndian(int val, char *buf);
char *serializeBool(int data, char *buf);
char *serializeBoolMsg(BoolMsg *msg, char *buf);
void printBool(struct BoolMsg *d);

#endif // SERIALIZER_H