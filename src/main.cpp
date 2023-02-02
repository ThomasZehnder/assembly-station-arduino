#include <Arduino.h>

#include "HttpServer.h"
#include "MqttServer.h"
#include "HwInterface.h"
#include "Oled.h"
#include "Ws2812.h"

#include "duktape/hello/duktapeHello.h" 

#include "Global.h"

#include "tiny-js/ArduinoTinyJs.h"

void setup()
{
    Serial.begin(115200);
    Serial.println();

    Assembly.setup(); //read config file

    ws2812Setup();
    oledSetup();

    //scanNetworks(); // call before httpSetup, show result in serial out
    oledShowNetworks(); // show result on OLED

    mqttSetup(); // call before httpSetup, to engage callback functions

    httpSetup(); // will block until WLAN connected

    hwSetup();
    
    tinyJsSetup();
}



void loop()
{

    hwLoop();

    // secound tick
    if (hwSecoundTick())
    {
        if (Assembly.mqttConnected)
        {
            mqttPublishLong("assembly-001/millis", hwGetMillis());
            mqttPublishLong("assembly-001/jitter", hwGetMillis() % 1000);
            mqttPublishLong("assembly-001/rssi", httpRssi());
        }
        if (Assembly.getProcessState() == "boot")
        {
            ws2812Demo();
        }

        //js interpreter test 1

        tinyJsLoop();

    }
    // 10ms tick
    if (hwCentiSecoundTick())
    {
        oledLoop();
        ws2812Loop();

        pollKeyPressed();
        hwKeyMqttPublish();

        Assembly.processKeys();

        if (Assembly.getChangeState())
        {
            mqttPublishString("assembly-001/processState", Assembly.getProcessState());
            ledSetState(Assembly.getProcessState());
        }
    }

    mqttLoop();
    httpLoop();
}