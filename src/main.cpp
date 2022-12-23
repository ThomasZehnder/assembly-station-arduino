#include <Arduino.h>

#include "HttpServer.h"
#include "MqttServer.h"
#include "HwInterface.h"

void setup()
{
    Serial.begin(115200);
    Serial.println();

    mqttSetup();
    httpSetup();
    hwSetup();
}

void loop()
{

    hwLoop();

    // secound tick
    if (hwSecoundTick())
    {
        mqttPublishLong("assembly-001/millis", hwGetMillis());
        mqttPublishLong("assembly-001/rssi", httpRssi());
    }

    mqttLoop();
    httpLoop();
}