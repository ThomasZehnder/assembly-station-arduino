tiny-js
=======

(originally [on Google Code](https://code.google.com/p/tiny-js/))

This project aims to be an extremely simple (~2000 line) JavaScript interpreter, meant for 
inclusion in applications that require a simple, familiar script language that can be included
with no dependencies other than normal C++ libraries. It currently consists of two source files:
one containing the interpreter, another containing built-in functions such as String.substring.

TinyJS is not designed to be fast or full-featured. However it is great for scripting simple 
behaviour, or loading & saving settings.

I make absolutely no guarantees that this is compliant to JavaScript/EcmaScript standard. 
In fact I am sure it isn't. However I welcome suggestions for changes that will bring it 
closer to compliance without overly complicating the code, or useful test cases to add to 
the test suite.

Currently TinyJS supports:

* Variables, Arrays, Structures
* JSON parsing and output
* Functions
* Calling C/C++ code from JavaScript
* Objects with Inheritance (not fully implemented)

Please see [CodeExamples](https://github.com/gfwilliams/tiny-js/blob/wiki/CodeExamples.md) for examples of code that works...

For a list of known issues, please see the comments at the top of the TinyJS.cpp file, as well as the [GitHub issues](https://github.com/gfwilliams/tiny-js/issues)

There is also the [42tiny-js branch](https://github.com/gfwilliams/tiny-js/tree/42tiny-js) - this is maintained by Armin and provides a more full-featured JavaScript implementation than GitHub master.

TinyJS is released under an MIT licence.

Internal Structure
------------------------

TinyJS uses a Recursive Descent Parser, so there is no 'Parser Generator' required. It does not
compile to an intermediate code, and instead executes directly from source code. This makes it 
quite fast for code that is executed infrequently, and slow for loops.

Variables, Arrays and Objects are stored in a simple linked list tree structure (42tiny-js uses a C++ Map).
This is simple, but relatively slow for large structures or arrays.

## JavaScript function
--------------------------------
### ESP Interface functions

    Esp.setLed(i, color); //set led i[0..3] with color [#rrggbb]
    Esp.getKey(i); //get key status i[0..2]
    Esp.getKeyCounter(i); //get key couter of clicks i[0..2]

    tbd
    OLED

### Math function

    // --- Math and Trigonometry functions ---
    Math.abs(a)", scMathAbs, 0);
    Math.round(a)", scMathRound, 0);
    Math.min(a,b)", scMathMin, 0);
    Math.max(a,b)", scMathMax, 0);
    Math.range(x,a,b)", scMathRange, 0);
    Math.sign(a)", scMathSign, 0);
    
    Math.PI()", scMathPI, 0);
    Math.toDegrees(a)", scMathToDegrees, 0);
    Math.toRadians(a)", scMathToRadians, 0);
    Math.sin(a)", scMathSin, 0);
    Math.asin(a)", scMathASin, 0);
    Math.cos(a)", scMathCos, 0);
    Math.acos(a)", scMathACos, 0);
    Math.tan(a)", scMathTan, 0);
    Math.atan(a)", scMathATan, 0);
    Math.sinh(a)", scMathSinh, 0);
    Math.asinh(a)", scMathASinh, 0);
    Math.cosh(a)", scMathCosh, 0);
    Math.acosh(a)", scMathACosh, 0);
    Math.tanh(a)", scMathTanh, 0);
    Math.atanh(a)", scMathATanh, 0);
       
    Math.E()", scMathE, 0);
    Math.log(a)", scMathLog, 0);
    Math.log10(a)", scMathLog10, 0);
    Math.exp(a)", scMathExp, 0);
    Math.pow(a,b)", scMathPow, 0);
    
    Math.sqr(a)", scMathSqr, 0);
    Math.sqrt(a)", scMathSqrt, 0);    
  
### JS Functions
    exec(jsCode)", scExec, tinyJS); // execute the given code
    eval(jsCode)", scEval, tinyJS); // execute the given string (an expression) and return the result
    trace()", scTrace, tinyJS);  // 
    Object.dump()", scObjectDump, 0);
    Object.clone()", scObjectClone, 0);
    Math.rand()", scMathRand, 0);
    Math.randInt(min, max)", scMathRandInt, 0);
    charToInt(ch)", scCharToInt, 0); //  convert a character to an int - get its value
    String.indexOf(search)", scStringIndexOf, 0); // find the position of a string in a string, -1 if not
    String.substring(lo,hi)", scStringSubstring, 0);
    String.charAt(pos)", scStringCharAt, 0);
    String.charCodeAt(pos)", scStringCharCodeAt, 0);
    String.fromCharCode(char)", scStringFromCharCode, 0);
    String.split(separator)", scStringSplit, 0);
    Integer.parseInt(str)", scIntegerParseInt, 0); // string to int
    Integer.valueOf(str)", scIntegerValueOf, 0); // value of a single character
    //TZE 20230205 unsafe, crashes
    //JSON.stringify(obj, replacer)", scJSONStringify, 0); // convert to JSON. replacer is ignored at the moment
    // JSON.parse is left out as you can (unsafely!) use eval instead
    Array.contains(obj)", scArrayContains, 0);
    Array.remove(obj)", scArrayRemove, 0);
    Array.join(separator)", scArrayJoin, 0);

