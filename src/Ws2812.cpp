#include "Ws2812.h"
#include "Arduino.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define WS2812_PIN D3

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

// double ring has 40 leds
//  assembly is equiped with 4 leds
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, WS2812_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait)
{
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(strip.numPixels() - i - 1, c);
        strip.show();
        delay(wait);
    }
}
#define DEMO_DELAY 50
void fullColorWipe(bool mode)
{
    Serial.println("fullColorWipe --> Start");
    // Some example procedures showing how to display to the pixels:
    colorWipe(strip.Color(32, 32, 32),DEMO_DELAY); // White RGB
    colorWipe(strip.Color(16, 0, 0), DEMO_DELAY); // Red
    
    if (mode)
    {
        colorWipe(strip.Color(0, 0, 255), DEMO_DELAY); // Blue
    }
    else
    {
        
        colorWipe(strip.Color(0, 32, 0), DEMO_DELAY); // Green
    }
}

void ws2812Setup()
{
    Serial.println("Ws2812Setup --> Start");

    strip.begin();
    strip.setBrightness(50);
    strip.clear();
    strip.show(); // Initialize all pixels to 'off'

    Serial.println("Ws2812Setup --> End");
}

int ledIdx = 0;
byte ledColor = 0;

void ws2812Demo(void)
{
    uint32_t c = strip.Color(0, 0, 0);
    strip.setPixelColor(ledIdx, c); // reset old led

    ledColor++;
    ledIdx--;
    if (ledIdx < 0)
    {
        ledIdx = strip.numPixels() - 1;
    }

    if (ledColor % 3 == 0)
    {
        c = strip.Color(16, 0, 0); // red
    }
    else if (ledColor % 3 == 1)
    {
        c = strip.Color(0, 32, 0); // green
    }
    else
    {
        c = strip.Color(0, 0, 255); // blue
    }

    strip.setPixelColor(ledIdx, c);
    strip.show();
}

void ledSetState(String s)
{
    strip.clear();
    if (s == "new")
    {
        strip.setPixelColor(3, strip.Color(0, 0, 255)); // blue
    }
    else if (s == "started")
    {
        // strip.setPixelColor(3, strip.Color(0, 0, 128)); // blue
        strip.setPixelColor(2, strip.Color(16, 32, 128)); // white
    }
    else if (s == "finished")
    {
        strip.setPixelColor(1, strip.Color(0, 32, 0)); // green
    }
    else if (s == "aborted")
    {
        strip.setPixelColor(0, strip.Color(16, 0, 0)); // red
    }
    strip.show();
}

void ws2812Loop()
{
    //
}