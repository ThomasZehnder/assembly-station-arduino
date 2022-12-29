#include "Global.h"

// global object definition
clAssembly Assembly;

void clAssembly::startProcess()
{
    processState = 1;
}

void clAssembly::finishProcess()
{
    processState = 2;
}

void clAssembly::abortProcess()
{
    processState = 3;
}

String clAssembly::getProcessState()
{
    if (processState == 1)
    {
        return String("started");
    }
    else if (processState == 2)
    {
        return String("finished");
    }
    else if (processState == 3)
    {
        return String("aborted");
    }
    else
    {
        return String("undef");
    }
}