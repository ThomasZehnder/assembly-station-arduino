#include <Arduino.h>

#include "HttpServer.h"
#include "MqttServer.h"

void setup()
{
    Serial.begin(115200);
    Serial.println();

    mqttSetup();
    httpSetup();
}

void loop()
{
    mqttLoop();
    httpLoop();
}