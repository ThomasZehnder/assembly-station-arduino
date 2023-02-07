#include <ArduinoJson.h>
#include "TinyJS.h"

class ArduinoTinyJs
{
public:

    int loopCounter;

    //JS program parts
    String initStr;
    String cyclicStr;
    String exitStr;

    //error string
    String errorStr;
    bool errorActive;

    //cyclic run flags
    bool setCmd(String cmd);
    bool singleRun;
    bool cyclicRun;

    //Array used for "print"
    #define CONSOLE_LEN 10
    String consoleStr[CONSOLE_LEN];
    const byte consoleStrLength=CONSOLE_LEN;
    int consoleCounter;

    ArduinoTinyJs(); // constructor

    void setup();
    void loop();
    void tearDown();

    void loadSetup();
    void loadLoop();
    void loadTearDown();

    //time meassurment
    unsigned long startTime;
    unsigned long executeTime;
    unsigned long cycleTime;

private:
    // create instance dynamic
    CTinyJS *js;

    void execute(const String * code, const char * context);
    void load(String * code, const char * filename);

};

extern ArduinoTinyJs tinyJs;
