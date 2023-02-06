/*
 * TinyJS
 *
 *  ESP functions specialized for ESP IIoT board
 */

#include <Arduino.h>

#include "Ws2812.h"

#include "TinyJS_EspFunctions.h"

// CScriptVar shortcut macro
#define scIsBool(a) (c->getParameter(a)->isBool())
#define scIsInt(a) (c->getParameter(a)->isInt())
#define scIsDouble(a) (c->getParameter(a)->isDouble())
#define scIsString(a) (c->getParameter(a)->isString())
#define scGetBool(a) (c->getParameter(a)->getBool())
#define scGetInt(a) (c->getParameter(a)->getInt())
#define scGetDouble(a) (c->getParameter(a)->getDouble())
#define scGetString(a) (c->getParameter(a)->getString())
#define scReturnBool(a) (c->getReturnVar()->setBool(a))
#define scReturnInt(a) (c->getReturnVar()->setInt(a))
#define scReturnDouble(a) (c->getReturnVar()->setDouble(a))
#define scReturnString(a) (c->getReturnVar()->setString(a))
#define scReturnUndefined() (c->getReturnVar()->setUndefined())

// Esp.SetLed(pixel, color); //set led pixel[0..3] with color [#rrggbb, off/black, red, green, blue, white]
void scEspSetLed(CScriptVar *c, void *)
{
    if (scIsInt("pixel") && scIsString("color"))
    {
        int i = scGetInt("pixel");
        String color = String(scGetString("color").c_str());

        if (color.startsWith("#"))
        {
            long int rgb = strtoul(color.substring(1, color.length()).c_str(), nullptr, 16); //=>rgb=0x001234FE;
            byte r = (byte)(rgb >> 16);
            byte g = (byte)(rgb >> 8);
            byte b = (byte)(rgb);

            strip.setPixelColor(i, strip.Color(r, g, b)); // white
        }
        else if (color == "red")
        {
            strip.setPixelColor(i, strip.Color(16, 0, 0)); // red
        }
        else if (color == "green")
        {
            strip.setPixelColor(i, strip.Color(0, 32, 0)); // green
        }
        else if (color == "yellow")
        {
            strip.setPixelColor(i, strip.Color(16, 16, 0)); // yellow
        }
        else if (color == "blue")
        {
            strip.setPixelColor(i, strip.Color(0, 0, 255)); // blue
        }
        else if ((color == "white") || (color == "on"))
        {
            strip.setPixelColor(i, strip.Color(16, 32, 255)); // white
        }
        else if ((color == "black") || (color == "off"))
        {
            strip.setPixelColor(i, strip.Color(0, 0, 0)); // off
        }
        else
        {
            strip.setPixelColor(i, strip.Color(8, 16, 127)); // white 50% brigtness
        }

        strip.show();
    }
    scReturnUndefined();
}

void scEspClearLed(CScriptVar *c, void *)
{
    strip.clear();
    strip.show();
    scReturnUndefined();
}

// ----------------------------------------------- Register Functions
void registerEspFunctions(CTinyJS *tinyJS)
{

    // --- ESP and Arduino functions ---
    tinyJS->addNative("function Esp.SetLed(pixel, color)", scEspSetLed, 0); // Set WS2812 Strip LED, i index of pixel, color
    tinyJS->addNative("function Esp.ClearLed()", scEspClearLed, 0);         // turn of all WS2812 Strip Leds
}
