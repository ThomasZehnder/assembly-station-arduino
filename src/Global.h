#ifndef GLOBAL_H
#define GLOBAL_H
// global object definition
#include <Arduino.h>

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

private:
    int processState = 0;

public:
    void startProcess();
    void finishProcess();
    void abortProcess();
};

extern clAssembly Assembly;

#endif //GLOBAL_H