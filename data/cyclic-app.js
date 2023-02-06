// java script cyclic
if (1 = 0) {
    print('CYCLIC from File');

    function dec(x) {
        x--;
        return x;
    }
    x++;

    print('x=' + x);

    y = inc(y);

    print('y=' + y);

    //not working, CRASH !!!
    //print(JSON.stringify({a:7}));
    var r = Math.rand();
    print(r);
    print(Math.randInt(2, 10));
}

//fom Math package 

//print("sin of " + r + "=" + Math.sin(r));
if (x >= 20) {
    Esp.clearLed();
    x = 0;
}
var c = "on";//white
if (x >= 2) c = "green";
if (x >= 4) c = "red";
if (x >= 6) c = "yellow";
if (x >= 8) c = "off";//black
if (x >= 10) c = "#FF0000";//red
if (x >= 12) c = "#00FF00";//green
if (x >= 14) c = "#FFFFFF";//white full brightness
if (x >= 16) c = "x";//white 50% brightness to showerror
print(x);
Esp.setLed(x % 4, c);
x++;

print("Key[0] = " + Esp.getKey(0));
print("Key[0]Counter = " + Esp.getKeyCounter(0));
if (Esp.getKey(0)) {
    Esp.setLed(0, "#FFFFFF");
}
else {
    Esp.setLed(0, "off");
}