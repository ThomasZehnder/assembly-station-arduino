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
    int pin;
    bool pressed;
    bool oldState;
    int pressedCounter;

    bool wifiConnected = false;
    bool mqttConnected = false;
    String localIp;

    struct tstKey keys[3];

private:
    int processState = 0;

public:
    void startProcess();
    void finishProcess();
    void abortProcess();

    String getProcessState();
};

extern clAssembly Assembly;

#endif //GLOBAL_H