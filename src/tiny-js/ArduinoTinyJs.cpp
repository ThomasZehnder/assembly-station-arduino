/*
 * Arduino Interface with TinyJS
 */

#include "TinyJS.h"
#include "TinyJS_Functions.h"
// #include <assert.h>
// #include <stdio.h>
#include <Arduino.h>

#include "ArduinoTinyJs.h"

ArduinoTinyJs tinyJs;

// const char *code = "var a = 5; if (a==5) a=4; else a=3;";
// const char *code = "{ var a = 4; var b = 1; while (a>0) { b = b * 2; a = a - 1; } var c = 5; }";
// const char *code = "{ var b = 1; for (var i=0;i<4;i=i+1) b = b * 2; }";
// const char *code = "function myfunc(x, y) { return x + y; } var a = myfunc(1,2); print(a);";

void js_print(CScriptVar *v, void *userdata)
{
  Serial.print(">> ");
  Serial.println(v->getParameter("text")->getString().c_str());
}

void js_dump(CScriptVar *v, void *userdata)
{
  CTinyJS *js = (CTinyJS *)userdata;
  js->root->trace(">  ");
}

void ArduinoTinyJs::setup()
{
  Serial.println("TinyJsSetup...Start");

  errorStr = "setup started...";
  errorActive = false;

  if (js)
  {
    delete js;
  }

  // create instance dynamic
  js = new CTinyJS();

  /* add the functions from TinyJS_Functions.cpp */
  registerFunctions(js);
  /* Add a native function */
  js->addNative("function print(text)", &js_print, 0);
  js->addNative("function dump()", &js_dump, js);

  // load from file
  loadSetup();
  loadLoop();
  loadTearDown();

  // execute INIT
  execute(&initStr, "INIT");

  Serial.println("TinyJsSetup...End");
}

void ArduinoTinyJs::loop()
{

  if (!errorActive)
  {
    loopCounter++;
    Serial.print("tinyJsLoop Start: ");
    Serial.println(loopCounter);
    execute(&cyclicStr, "CYCLIC");
  }
  else
  {
    Serial.print("tinyJsLoop Error: ");
    Serial.println(errorStr);
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
    Serial.print(" ERROR: ");
    Serial.println(e->text.c_str());
    errorStr = (String)e->text.c_str();
    errorActive = true;
  }
  catch (...)
  {
    Serial.print(context);
    Serial.println(" ERROR: Catch all...");
    errorStr = "unknown exeption";
    errorActive = true;
  }
}

// constructor
ArduinoTinyJs::ArduinoTinyJs()
{
  setupCmd = false;
  loopCmd = false;

  printStr[0] = "constructor";
  loopCounter = 0;

  initStr = "print('init default'); dump();";
  cyclicStr = "print('cyclic default');";

  errorActive = false;
}
