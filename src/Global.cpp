
#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#include "Global.h"
#include "credentials.h"

// global object definition
clAssembly Assembly;

// Inside the brackets, 200 is the capacity of the memory pool in bytes.
// Don't forget to change this value to match your JSON document.
// Use http://arduinojson.org/v6/assistant to compute the capacity.
StaticJsonDocument<512> doc;

void SerialFileOut(const char *filename)
{

    File file = LittleFS.open(filename, "r"); // Open the file
    // print out filecontent
    Serial.println(String("Assembly.setup --> configfile: ") + filename + " found... size:" + file.size());

    while (file.available())
    {
        Serial.write(file.read());
    }
    Serial.println();
    file.close(); // Close the file again
}

void clAssembly::setupWifi()
{
    char filename[] = "/config_wlan.json";

    if (LittleFS.exists(filename))
    {
        SerialFileOut(filename);

        File file = LittleFS.open(filename, "r"); // Open the file again

        // parse JSON
        DeserializationError error = deserializeJson(doc, file);

        // Test if parsing succeeds.
        if (error)
        {
            Serial.print(F("Assembly.setup --> deserializeJson() failed: "));
            Serial.println(error.f_str());
        }

        // assigne values
        // get array size

        // Serial.println(String("Assembly.setup --> configfile number of entries: ") + doc.size());
        byte i = 0;
        for (JsonObject item : doc.as<JsonArray>())
        {
            if (i < (sizeof(cfg.wifi) / sizeof(cfg.wifi[0])))
            {
                strncpy(cfg.wifi[i].ssid, item["SSID"] | WIFI_SSID, sizeof(cfg.wifi[i].ssid));
                strncpy(cfg.wifi[i].pw, item["PASSWORD"] | WIFI_PASSWORD, sizeof(cfg.wifi[i].pw));

                Serial.println(String("Assembly.setup --> entry: ") + i + " / " + cfg.wifi[i].ssid + " / " + cfg.wifi[i].pw);
            }

            i++;
        }

        file.close(); // Close the file again
    }
    else
    {
        Serial.println(String("Assembly.setup --> error: NO ") + filename + " found, works with default defines.");
        strncpy(cfg.wifi[0].ssid, WIFI_SSID, sizeof(cfg.wifi[0].ssid));
        strncpy(cfg.wifi[0].pw, WIFI_PASSWORD, sizeof(cfg.wifi[0].pw));
        strncpy(cfg.wifi[1].ssid, WIFI_SSID_1, sizeof(cfg.wifi[1].ssid));
        strncpy(cfg.wifi[1].pw, WIFI_PASSWORD_1, sizeof(cfg.wifi[1].pw));
        strcpy(cfg.wifi[2].ssid, "" );
        strcpy(cfg.wifi[3].pw, "" );
    }
}

// read configuration from file
void clAssembly::setup()
{
    Serial.println("Assembly.setup --> begin");

    if (!LittleFS.begin())
    {
        Serial.println("Assembly.setup --> An Error has occurred while mounting LittleFS");
        delay(1000);
    }

    setupWifi();

    Serial.println("Assembly.setup --> end");
}

void clAssembly::newProcess()
{
    processState = 1;
    changedState = true;
}
void clAssembly::startProcess()
{
    processState = 11;
    changedState = true;
}

void clAssembly::finishProcess()
{
    processState = 12;
    changedState = true;
}

void clAssembly::abortProcess()
{
    processState = 13;
    changedState = true;
}
void clAssembly::wlanConnectedProcess()
{
    processState = 21;
    changedState = true;
}
void clAssembly::rebootProcess()
{
    processState = 31;
    changedState = true;
}

// gettter will reset flag
bool clAssembly::getChangeState()
{
    bool returnValue = changedState;
    changedState = false;
    return returnValue;
}

String clAssembly::getProcessState()
{
    if (processState == 1)
    {
        return String("new");
    }
    else if (processState == 11)
    {
        return String("started");
    }
    else if (processState == 12)
    {
        return String("finished");
    }
    else if (processState == 13)
    {
        return String("aborted");
    }
    else if (processState == 21)
    {
        return String("wlanOk");
    }
    else if (processState == 31)
    {
        return String("reboot");
    }
    else
    {
        return String("boot");
    }
}

void clAssembly::processKeys()
{
    if (keys[0].pressed)
    {
        startProcess();
    }
    else if (keys[1].pressed)
    {
        finishProcess();
    }
    else if (keys[2].pressed)
    {
        abortProcess();
    }
}
