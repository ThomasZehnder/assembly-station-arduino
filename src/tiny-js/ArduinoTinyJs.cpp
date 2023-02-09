/*
 * Arduino Interface with TinyJS
 */

#include "TinyJS.h"
#include "TinyJS_Functions.h"
#include "TinyJS_MathFunctions.h"
#include "TinyJS_EspFunctions.h"

#include <Arduino.h>

#include "ArduinoTinyJs.h"

ArduinoTinyJs tinyJs;

// const char *code = "var a = 5; if (a==5) a=4; else a=3;";
// const char *code = "{ var a = 4; var b = 1; while (a>0) { b = b * 2; a = a - 1; } var c = 5; }";
// const char *code = "{ var b = 1; for (var i=0;i<4;i=i+1) b = b * 2; }";
// const char *code = "function myfunc(x, y) { return x + y; } var a = myfunc(1,2); print(a);";

void js_print(CScriptVar *v, void *userdata)
{

  // shift Console Out
  for (byte i = tinyJs.consoleStrLength - 1; i > 0; i--)
  {
    tinyJs.consoleStr[i] = tinyJs.consoleStr[i - 1];
  }

  // write to Console
  tinyJs.consoleStr[0] = String(tinyJs.consoleCounter) + ": " + String(v->getParameter("text")->getString().c_str());

  Serial.println(tinyJs.consoleStr[0]);

  tinyJs.consoleCounter++;
}

void js_dump(CScriptVar *v, void *userdata)
{
  CTinyJS *js = (CTinyJS *)userdata;
  js->root->trace(">  ");
}

void ArduinoTinyJs::setup()
{
  Serial.println("TinyJsSetup...Start");

  errorStr = "no error, setup started...";
  errorActive = false;

  if (js)
  {
    delete js;
  }

  // create instance dynamic
  js = new CTinyJS();

  /* add the functions from TinyJS_Functions.cpp */
  registerFunctions(js);
  registerMathFunctions(js); //no trigonomic functions
  registerEspFunctions(js);

  /* Add a native function */
  js->addNative("function print(text)", &js_print, 0);
  js->addNative("function dump()", &js_dump, js);

  // load from file
  loadSetup();
  loadLoop();
  loadTearDown();

  // init counter
  loopCounter = 0;
  consoleCounter = 0;

  // execute INIT
  execute(&initStr, "INIT");

  Serial.println("TinyJsSetup...End");
}

void ArduinoTinyJs::loop()
{


  if (!errorActive && (singleRun||cyclicRun))
  {
    loopCounter++;
    
    Serial.print("tinyJsLoop Start: ");
    Serial.println(loopCounter);
    cycleTime = millis() - startTime;
    startTime = millis();
    execute(&cyclicStr, "CYCLIC");
    executeTime = millis()-startTime;
    if (singleRun){
      singleRun = false;
      Serial.println("tinyJsLoop Stopped");
    }
  }

}

void ArduinoTinyJs::tearDown()
{
  execute(&exitStr, "EXIT");

  delete js;
  js = NULL;
}

void ArduinoTinyJs::execute(const String *code, const char *context)
{
  try
  {
    // execute file content loaded
    js->execute(code->c_str());
  }
  catch (CScriptException *e)
  {
    Serial.print(context);
    Serial.print("ArduinoTinyJs ERROR: ");
    Serial.println(e->text.c_str());
    errorStr = (String)e->text.c_str();
    errorActive = true;
  }
  catch (...)
  {
    Serial.print(context);
    Serial.println("ArduinoTinyJs ERROR: Catch all...");
    errorStr = "unknown exeption";
    errorActive = true;
  }
}

/*
<button class="warning" onclick="sendReboot('initboot')">RESTART INIT</button>
<button class="warning" onclick="sendReboot('cyclicboot')">RESTART CYCLIC</button>
<button onclick="sendReboot('singlerun')">Single Run</button>
<button onclick="sendReboot('cyclicrun')">Cyclic Run</button>
*/
bool ArduinoTinyJs::setCmd(String arg)
{
  if (arg == "initboot")
  {
    tearDown();
    setup();
    return true;
  }
  else if (arg == "cyclicboot")
  {
    loadLoop(); // only load cyclic code new
    errorStr = "restart cyclic js";
    errorActive = false;
    return true;
  }
    else if (arg == "singlerun")
  {
    loadLoop(); // only load cyclic code new
    errorStr = "single run active";
    singleRun = true;
    cyclicRun = false;
    errorActive = false;
    return true;
  }
    else if (arg == "cyclicrun")
  {
    loadLoop(); // only load cyclic code new
    errorStr = "cyclic run active";
    singleRun = false;
    cyclicRun = true;
    errorActive = false;
    return true;
  }
  return false;
}

// constructor
ArduinoTinyJs::ArduinoTinyJs()
{
  consoleStr[0] = "constructor";
  loopCounter = 0;
  consoleCounter = 0;

  initStr = "print('init default');";
  cyclicStr = "print('cyclic default');";
  exitStr = "print('exit default');";

  errorActive = false;
  cyclicRun = true; 
}
