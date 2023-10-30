#include <Arduino.h>
#include <wifi_setup.h>

void connect_wifi()
{
    // Initialize Serial for debug
    Serial.begin(9600);
    while (!Serial)
    {
        delay(1000);
    }

    Serial.print("Trying to connect in ");
    Serial.print(SSID);
    Serial.print(" ...\n");

    // Set WiFi in STA mode and trigger attachment
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASS);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
    }
    Serial.println("Connected to WiFi!");
}
