#include <ArduinoJson.h>
#include "TinyJS.h"

class ArduinoTinyJs
{
public:
    bool setupCmd; //reload INIT and start CYCLIC
    bool loopCmd; //restart only cyclic

    int loopCounter;

    String initStr;
    String cyclicStr;
    String exitStr;

    //error string
    String errorStr;

    //Array used for "print"
    String printStr[10];

    ArduinoTinyJs(); // constructor

    void setup();
    void loop();
    void tearDown();

private:
    // create instance dynamic
    CTinyJS *js;

};


extern ArduinoTinyJs tinyJs;
