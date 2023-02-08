#ifndef GLOBAL_H
#define GLOBAL_H
// global object definition
#include <Arduino.h>

struct tstCfgWifi
{
    char ssid[32];
    char pw[32];
};

struct tstCfgMqtt
{
    int port;
    char host[32];
    byte hostIp[4]; // 4 digits

    char login[32];
    char pw[32];
};

#define NBRCONNECTIONS 3
struct tstCfg
{
    tstCfgWifi wifi[NBRCONNECTIONS];
    tstCfgMqtt mqtt[NBRCONNECTIONS];
};

struct tstKey
{
    int pin;
    bool edge; 
    bool pressed;
    int pressedCounter;
};

class clAssembly
{
public:
    String compileDate;
    char deviceId[32];

    bool wifiConnected = false;
    bool mqttConnected = false;
    String localIp;
    String ssid;
    String mqttBroker;

    struct tstKey keys[3];

    tstCfg cfg;

private:
    int processState = 0;
    bool changedState = false;

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

private:
    void setupDevice();
    void setupWifi();
    void setupMqtt();
};

extern clAssembly Assembly;

#endif // GLOBAL_H