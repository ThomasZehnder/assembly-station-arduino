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

/*     mqttSetup();
    httpSetup();
    hwSetup();
    oledSetup(); */
    ws2812Setup();
}

void loop()
{

/*     hwLoop();

    // secound tick
    if (hwSecoundTick())
    {
        mqttPublishLong("assembly-001/millis", hwGetMillis());
        mqttPublishLong("assembly-001/jitter", hwGetMillis()%1000);
        mqttPublishLong("assembly-001/rssi", httpRssi());
    }

    mqttLoop();
    httpLoop();
    oledLoop(); */
    ws2812Loop();
}