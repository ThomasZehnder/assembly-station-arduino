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
    bool errorActive;

    //Array used for "print"
    String consoleStr[10];
    byte consoleStrLength;

    ArduinoTinyJs(); // constructor

    void setup();
    void loop();
    void tearDown();

    void loadSetup();
    void loadLoop();
    void loadTearDown();

private:
    // create instance dynamic
    CTinyJS *js;

    void execute(const String * code, const char * context);

    void load(String * code, const char * filename);

};


extern ArduinoTinyJs tinyJs;
