#include <Arduino.h>
#include <HwInterface.h>

int key1Click = 0;

// interval at which to blink (milliseconds)
const long SECOUND_INTERVAL = 1000;
unsigned long  preSecoundMillis = 0;
bool secoundTick = false;

// 10ms tick (milliseconds)
const long CENTI_SECOUND_INTERVAL = 10;
unsigned long  preCentiSecoundMillis = 0;
bool centiSecoundTick = false;

unsigned long  currentMillis = 0;

// ledState used to set the LED
int ledState = LOW;          


bool hwCentiSecoundTick(void){
    return centiSecoundTick;
}
bool hwSecoundTick(void){
    return secoundTick;
}

unsigned long hwGetMillis(void){
    return currentMillis;
}

void hwSetup(void)
{
    pinMode(TOGGLE_LED_PIN, OUTPUT);

    pinMode(KEY1_PIN, INPUT_PULLUP);
    pinMode(KEY2_PIN, INPUT_PULLUP);
    pinMode(KEY3_PIN, INPUT_PULLUP);   
}

void hwLoop(void)
{
    currentMillis = millis();
    // secound tick
    if ((long)(currentMillis-preSecoundMillis) > 0)
    {
        preSecoundMillis += SECOUND_INTERVAL;
        secoundTick = true;

        // set the LED with the ledState of the variable:
        ledState = !ledState;
        digitalWrite(TOGGLE_LED_PIN, ledState);

    } else {
        secoundTick = false;
    }
    //10ms tick
    if ((long)(currentMillis-preCentiSecoundMillis) > 0)
    {
        preCentiSecoundMillis += CENTI_SECOUND_INTERVAL;
        centiSecoundTick = true;


    } else {
        centiSecoundTick = false;
    }
}