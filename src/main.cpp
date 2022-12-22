#include <Arduino.h>

#include "HttpServer.h"
#include "MqttServer.h"

const long interval = 1000; // interval at which to blink (milliseconds)
long previousMillis = millis();

const int toggelLedPin = D0; // the number of the LED pin
int ledState = LOW;          // ledState used to set the LED

void setup()
{
    Serial.begin(115200);
    Serial.println();

    mqttSetup();
    httpSetup();

    pinMode(toggelLedPin, OUTPUT);
}

void loop()
{
    mqttLoop();
    httpLoop();

    // secound tick
    unsigned long currentMillis = millis();
    if ((long)(currentMillis)-previousMillis - interval > 0)
    {
        previousMillis = currentMillis/1000*1000;
        ledState = !ledState;
        // set the LED with the ledState of the variable:
        digitalWrite(toggelLedPin, ledState);

        mqttPublishLong("test/livemillis", currentMillis);

        mqttPublishLong("test/rssi", httpRssi());
    }
}