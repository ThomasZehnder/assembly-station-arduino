#include <Arduino.h>
#include <HwInterface.h>

#include "MqttServer.h"

#include "Global.h"

// interval at which to blink (milliseconds)
const long SECOUND_INTERVAL = 1000;
unsigned long preSecoundMillis = 0;
bool secoundTick = false;

// 10ms tick (milliseconds)
const long CENTI_SECOUND_INTERVAL = 10;
unsigned long preCentiSecoundMillis = 0;
bool centiSecoundTick = false;

unsigned long currentMillis = 0;

// ledState used to set the LED
int ledState = LOW;

bool hwCentiSecoundTick(void)
{
    return centiSecoundTick;
}
bool hwSecoundTick(void)
{
    return secoundTick;
}

unsigned long hwGetMillis(void)
{
    return currentMillis;
}

void hwSetup(void)
{
    pinMode(TOGGLE_LED_PIN, OUTPUT);

    Assembly.keys[0].pin = KEY1_PIN;
    Assembly.keys[1].pin = KEY2_PIN;
    Assembly.keys[2].pin = KEY3_PIN;

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        pinMode(Assembly.keys[i].pin, INPUT_PULLUP);
    }
}

void hwLoop(void)
{
    currentMillis = millis();
    // secound tick
    if ((long)(currentMillis - preSecoundMillis) > 0)
    {
        // Blink fast if not connected
        if (!Assembly.mqttConnected)
        {
            preSecoundMillis = currentMillis + SECOUND_INTERVAL / 5;
        }
        else
        {
            preSecoundMillis += SECOUND_INTERVAL;
        }

        secoundTick = true;

        // set the LED with the ledState of the variable:
        ledState = !ledState;
        digitalWrite(TOGGLE_LED_PIN, ledState);
    }
    else
    {
        secoundTick = false;
    }
    // 10ms tick
    if ((long)(currentMillis - preCentiSecoundMillis) > 0)
    {
        preCentiSecoundMillis += CENTI_SECOUND_INTERVAL;
        centiSecoundTick = true;
    }
    else
    {
        centiSecoundTick = false;
    }
}

// getter
bool keyPressed(int keyNumber)
{
    return Assembly.keys[keyNumber].pressed;
}
int keyPressedCounter(int keyNumber)
{
    return Assembly.keys[keyNumber].pressedCounter;
}

// key pressed detection
void pollKeyPressed(void)
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        bool state = digitalRead(Assembly.keys[i].pin);
        // false = pressed
        if ((state == false) && (state != Assembly.keys[i].oldState))
        {
            Assembly.keys[i].pressed = true;
            Assembly.keys[i].pressedCounter++;
        }
        else
        {
            Assembly.keys[i].pressed = false;
        }
        Assembly.keys[i].oldState = state;
    }
}

// Key pressed counter publisher
void hwKeyMqttPublish(void)
{
    if (keyPressed(0))
    {
        mqttPublishLong("assembly-001/key-1", keyPressedCounter(0));
    }
    if (keyPressed(1))
    {
        mqttPublishLong("assembly-001/key-2", keyPressedCounter(1));
    }
    if (keyPressed(2))
    {
        mqttPublishLong("assembly-001/key-3", keyPressedCounter(2));
    }
}
