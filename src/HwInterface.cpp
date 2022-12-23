#include <Arduino.h>
#include <HwInterface.h>

int key1Click = 0;

void hwSetup(void)
{
    pinMode(KEY1_PIN, INPUT_PULLUP);
    pinMode(KEY2_PIN, INPUT_PULLUP);
    pinMode(KEY3_PIN, INPUT_PULLUP);   
}

void hwLoop(void)
{

}