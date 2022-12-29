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