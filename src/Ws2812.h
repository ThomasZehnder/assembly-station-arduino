#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

void ws2812Setup(void);
void ws2812Loop(void);

void ws2812Demo(void);

void ledSetState(String);
void fullColorWipe(bool mode);

extern Adafruit_NeoPixel strip;