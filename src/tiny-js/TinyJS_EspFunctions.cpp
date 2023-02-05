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
#define scReturnUndefined (c->getReturnVar()->setUndefined())

// Esp.setLed(i, color); //set led i[0..3] with color [#rrggbb, off, red, green, blue, white]
void scEspSetLed(CScriptVar *c, void *userdata)
{
    if (scIsInt("i") && scIsString("color"))
    {
        int i = scGetInt("i");
        String color = String(scGetString("color").c_str());

        strip.setPixelColor(i, strip.Color(16, 0, 0)); // red
        strip.show();
    }
}

// ----------------------------------------------- Register Functions
void registerEspFunctions(CTinyJS *tinyJS)
{

    // --- ESP and Arduino functions ---
    tinyJS->addNative("Esp.setLed(i, color)", scEspSetLed, 0);
}
