#include <wifi/wifi_setup.h>

void connectWifi()
{
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
