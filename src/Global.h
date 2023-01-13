#ifndef GLOBAL_H
#define GLOBAL_H
// global object definition
#include <Arduino.h>

struct tstCfgWlan
{
    char ssid[32];
    char pw[32];
};

struct tstCfgMqtt
{
    int port;
    char host[32];
    byte hostIp[4]; // 4 digits
};

struct tstCfg
{
    tstCfgWlan wlan[3];
    tstCfgMqtt mqtt[3];
};


struct tstKey
{
    int pin;
    bool pressed;
    bool oldState;
    int pressedCounter;
};

class clAssembly
{
public:
    bool wifiConnected = false;
    bool mqttConnected = false;
    String localIp;

    struct tstKey keys[3];

private:
    int processState = 0;
    bool changedState = false;
    tstCfg cfg;

public:
    void setup();
    void newProcess();
    void startProcess();
    void finishProcess();
    void abortProcess();

    void rebootProcess();
    void wlanConnectedProcess();

    String getProcessState();
    bool getChangeState();

    void processKeys();
};

extern clAssembly Assembly;

#endif // GLOBAL_H