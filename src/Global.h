#ifndef GLOBAL_H
#define GLOBAL_H
// global object definition
#include <Arduino.h>

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

public:
    void startProcess();
    void finishProcess();
    void abortProcess();

    String getProcessState();
    bool getChangeState();

    void processKeys();
};

extern clAssembly Assembly;

#endif // GLOBAL_H