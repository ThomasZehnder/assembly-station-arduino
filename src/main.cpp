#include <Arduino.h>

#include "HttpServer.h"
#include "MqttServer.h"
#include "HwInterface.h"
#include "Oled.h"
#include "Ws2812.h"

void setup()
{
    Serial.begin(115200);
    Serial.println();

    ws2812Setup();

    scanNetworks(); // call before httpSetup

    mqttSetup(); // call before httpSetup, to engage callback functions

    httpSetup();

    hwSetup();
    oledSetup();
}

void loop()
{

    hwLoop();

    // secound tick
    if (hwSecoundTick())
    {
        // mqttPublishLong("assembly-001/millis", hwGetMillis());
        // mqttPublishLong("assembly-001/jitter", hwGetMillis() % 1000);
        mqttPublishLong("assembly-001/rssi", httpRssi());

        ws2812Demo();
    }
    // 10ms tick
    if (hwCentiSecoundTick())
    {
        oledLoop();
        ws2812Loop();

        pollKeyPressed();
        hwKeyMqttPublish();
    }

    mqttLoop();
    httpLoop();
}