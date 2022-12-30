#include "Global.h"

// global object definition
clAssembly Assembly;

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
// gettter will reset flag
bool clAssembly::getChangeState(){
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
    else
    {
        return String("undef");
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