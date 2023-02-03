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

/*
void js_dump(CScriptVar *v, void *userdata) {
    CTinyJS *js = (CTinyJS*)userdata;
    js->root->trace(">  ");
}
*/


void ArduinoTinyJs::setup()
{
  Serial.println("TinyJsSetup...Start");

  // create instance dynamic
  js = new CTinyJS();

  /* add the functions from TinyJS_Functions.cpp */
  registerFunctions(js);
  /* Add a native function */
  js->addNative("function print(text)", &js_print, 0);
  // js->addNative("function dump()", &js_dump, js);

  // like _INIT
  try
  {
    js->execute("var x = 0; x++; print(x);");
    js->execute("var y = 0; function inc(i) { i++; return i;}");
    
    //execute file content loaded
    js->execute(initStr.c_str());
    
  }
  catch (CScriptException *e)
  {
    Serial.print("INIT ERROR CScriptException: ");
    Serial.println(e->text.c_str());
  }
  catch (...)
  {
    Serial.println("INIT ERROR: Catch all...");
  }

  Serial.println("TinyJsSetup...End");
}

void ArduinoTinyJs::loop()
{
  loopCounter++;
  Serial.print("tinyJsLoop Start: ");
  Serial.println(loopCounter);
  // like _CYCLIC
  try
  {
    //
    // js->execute(code);
    // js->execute("var y = 0; function set_y() { y = 1; }");
    // js->execute("var y = 0; ");
    // js->execute("print('y='+y); set_y();print('y='+y);");

    //js->execute("var x = 0; x++; print(x);");
    js->execute("x++; print('x='+x);");
    js->execute("y = inc(y); print('y='+y);");

    //execute file content loaded
    js->execute(cyclicStr.c_str());

    //
    //js->execute("unknown_function();");
  }
  catch (CScriptException *e)
  {
    Serial.print("CYCLIC ERROR CScriptException: ");
    Serial.println(e->text.c_str());
  }
  catch (...)
  {
    Serial.println("CYCLIC ERROR: Catch all...");
  }

  // use static at the moment. later for reinit use -->
  //delete js;
}

void ArduinoTinyJs::tearDown()
{
  //like _EXIT
  delete js;
  js = NULL;
}

// constructor
ArduinoTinyJs::ArduinoTinyJs() {
   setupCmd = false;
   loopCmd = false;

   printStr[0] = "constructor";
   loopCounter = 0;

   initStr = "print('init default');";
   cyclicStr = "print('cyclic default');";
   
}
