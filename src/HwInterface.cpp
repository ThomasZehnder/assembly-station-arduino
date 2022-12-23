#include <Arduino.h>
#include <HwInterface.h>

int key1Click = 0;

 // interval at which to blink (milliseconds)
const long INTERVAL = 1000;
unsigned long  preMillis = 0;
unsigned long  currentMillis = 0;
bool secoundTick = false;

// 
const int toggelLedPin = TOGGLE_LED_PIN; // the number of the LED pin
int ledState = LOW;          // ledState used to set the LED

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
    // secound tick
    currentMillis = millis();
    if ((long)(currentMillis-preMillis) - INTERVAL > 0)
    {
        preMillis += 1000;
        secoundTick = true;

        // set the LED with the ledState of the variable:
        ledState = !ledState;
        digitalWrite(toggelLedPin, ledState);

    } else {
        secoundTick = false;
    }

}