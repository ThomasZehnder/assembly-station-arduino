#include <Arduino.h>
#include <HwInterface.h>

struct tstKey
{
    int pin;
    bool pressed;
    bool oldState;
    int pressedCounter;
};

struct tstKey keys[3];

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

    keys[0].pin = KEY1_PIN;
    keys[1].pin = KEY2_PIN;
    keys[2].pin = KEY3_PIN;

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        pinMode(keys[i].pin, INPUT_PULLUP);
    }
}

void hwLoop(void)
{
    currentMillis = millis();
    // secound tick
    if ((long)(currentMillis - preSecoundMillis) > 0)
    {
        preSecoundMillis += SECOUND_INTERVAL;
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

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        bool state = digitalRead(keys[i].pin);
        //false = pressed
        if ((state==false)&&(state!=keys[i].oldState)){
            keys[i].pressed = true;
            keys[i].pressedCounter++;
        } else {
            keys[i].pressed = false;
        }
        keys[i].oldState = state;
    }
}

bool keyPressed(int keyNumber)
{
    return keys[keyNumber].pressed;
}
int keyPressedCounter(int keyNumber)
{
    return keys[keyNumber].pressedCounter;
}