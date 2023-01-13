
#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

#include "Global.h"

// global object definition
clAssembly Assembly;

// Inside the brackets, 200 is the capacity of the memory pool in bytes.
// Don't forget to change this value to match your JSON document.
// Use http://arduinojson.org/v6/assistant to compute the capacity.
StaticJsonDocument<512> doc;

void SerialFileOut(const char * filename){

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

// read configuration from file
void clAssembly::setup()
{
    Serial.println("Assembly.setup --> begin");

    if (!LittleFS.begin())
    {
        Serial.println("Assembly.setup --> An Error has occurred while mounting LittleFS");
        delay(1000);
    }

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
        for (JsonObject item : doc.as<JsonArray>())
        {

            // const char *SSID = item["SSID"];
            const char *PASSWORD = item["PASSWORD"];

            // does not work String ssid((const char *)item["SSID"]);
            char ssid[32];
            strncpy(ssid, item["SSID"] | "undefined", sizeof(ssid));
            //int port = item["PORT"];

            Serial.println(String("Assembly.setup --> entry: ") + ssid + "/"+ PASSWORD);
        }

        // Serial.println(String("Assembly.setup --> configfile SSID: ") + array[0]["SSID"]);

        file.close(); // Close the file again
    }
    else
    {
        Serial.println(String("Assembly.setup --> error: NO ") + filename + " found, works with default defines.");
    }

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
