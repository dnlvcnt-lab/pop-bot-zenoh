#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>

extern "C"
{
#include "zenoh-pico.h"
}

// WiFi-specific parameters
#define SSID ""
#define PASS ""

#define CLIENT_OR_PEER 1 // 0: Client mode; 1: Peer mode
#if CLIENT_OR_PEER == 0
#define MODE "client"
#define CONNECT "" // If empty, it will scout
#elif CLIENT_OR_PEER == 1
#define MODE "peer"
#define CONNECT "udp/224.0.0.224:7446#iface=wlp0s20f3"
#else
#error "Unknown Zenoh operation mode. Check CLIENT_OR_PEER value."
#endif

#define KEYEXPR "rt/popbot/bumper"

/* --- PinOut --- */
const int bumperPin = 2;


/* ---  Structs --- */
struct BoolMsg
{
    int data;
};

/* --- Serialize Functions --- */
char *serialize_int_as_little_endian(int val, char *buf)
{
    int *c_val = &val;
    for (int i = 0; i < sizeof(int); ++i, ++buf)
    {
        *buf = 0xFF & (*c_val >> (i * 8));
    }
    return buf;
}

char *serialize_bool(int data, char *buf)
{
    buf = serialize_int_as_little_endian(data, buf);
    return buf;
}


void serialize_bool_msg(BoolMsg *msg, char *buf)
{
    // Serialize BoolMsg header for little endian
    *(buf++) = 0x00;
    *(buf++) = 0x01;
    *(buf++) = 0x00;
    *(buf++) = 0x00;
    buf = serialize_bool(msg->data, buf);
}


/* --- Print Functions --- */
void printBool(struct BoolMsg *d)
{
    Serial.print("Data: ");
    Serial.print(d->data);
}

/* --- Zenoh --- */
z_owned_publisher_t pub;


void setup(void)
{
    // Initialize Serial for debug
    Serial.begin(9600);
    while (!Serial)
    {
        delay(1000);
    }

    // Set WiFi in STA mode and trigger attachment
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
    }
    Serial.println("Connected to WiFi!");

    delay(300);

    // Initialize Zenoh Session and other parameters
    z_owned_config_t config = z_config_default();
    zp_config_insert(z_config_loan(&config), Z_CONFIG_MODE_KEY, z_string_make(MODE));
    if (strcmp(CONNECT, "") != 0)
    {
        zp_config_insert(z_config_loan(&config), Z_CONFIG_CONNECT_KEY, z_string_make(CONNECT));
    }

    // Open Zenoh session
    Serial.print("Opening Zenoh Session...");
    z_owned_session_t s = z_open(z_config_move(&config));
    if (!z_session_check(&s))
    {
        Serial.println("Unable to open session!\n");
        while (1)
            ;
    }
    Serial.println("OK");

    // Start the receive and the session lease loop for zenoh-pico
    zp_start_read_task(z_session_loan(&s), NULL);
    zp_start_lease_task(z_session_loan(&s), NULL);

    // Declare Zenoh publisher
    Serial.print("Declaring publisher for ");
    Serial.print(KEYEXPR);
    Serial.println("...");
    pub = z_declare_publisher(z_session_loan(&s), z_keyexpr(KEYEXPR), NULL);
    if (!z_publisher_check(&pub))
    {
        Serial.println("Unable to declare publisher for key expression!\n");
        while (1)
            ;
    }
    Serial.println("OK");
    Serial.println("Zenoh setup finished!");

    delay(300);
}

void loop()
{
    Serial.print("Working");
    delay(100);

    // Read bumper sensor values and scale them
    int bumperStatus = digitalRead(bumperPin) == HIGH;

    // Create ROS bool message
    BoolMsg measure;
    measure.data = bumperStatus;
    printBool(&measure);

    uint8_t bool_serialized_size = 4 + sizeof(int);
    char buf[bool_serialized_size];
    serialize_bool_msg(&measure, buf);
    Serial.println("");

    if (z_publisher_put(z_publisher_loan(&pub), (const uint8_t *)buf, bool_serialized_size, NULL) < 0)
    {
        Serial.println("Error while publishing data");
    } else {
        Serial.println("PUB OK: ");
    }
}
