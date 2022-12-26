#include <Arduino.h>

#include "HttpServer.h"
#include "MqttServer.h"
#include "HwInterface.h"
#include "Oled.h"
#include "Ws2812.h"

#include "LittleFS.h"

void checkFs(void)
{
    if (!LittleFS.begin())
    {
        Serial.println("An Error has occurred while mounting LittleFS");
        delay(1000);
        return;
    }

    File file = LittleFS.open("/test.txt", "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.println("File Content:");
    while (file.available())
    {
        Serial.write(file.read());
    }
    file.close();
    Serial.println("");
}

void setup()
{
    Serial.begin(115200);
    Serial.println();

    checkFs();

    ws2812Setup();

    scanNetworks();

    mqttSetup();
    httpSetup();
    hwSetup();
    oledSetup();
}

void loop()
{

    hwLoop();

    // secound tick
    /*
    if (hwSecoundTick())
    {
        mqttPublishLong("assembly-001/millis", hwGetMillis());
        mqttPublishLong("assembly-001/jitter", hwGetMillis() % 1000);
        mqttPublishLong("assembly-001/rssi", httpRssi());

        ws2812Demo();
    }
    */

    mqttLoop();
    httpLoop();
    oledLoop();
    ws2812Loop();
}