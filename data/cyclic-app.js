// java script cyclic
if (1 === 1) {
    print('CYCLIC from File');
    print("millis=" + Esp.millis());

    function dec(x) {
       x--;
        return x;
    }
    //x++;
    print('x=' + x);

    y = inc(y);
    print('y=' + y);

    var r = Math.rand();
    print(r);
    print(Math.randInt(2, 10));
}

//from Math package

//print("sin of " + r + "=" + Math.sin(r));

if (x >= 20) {
    Esp.clearLed();
    x = 0;
}

var c = "on";//white

if (x >= 16) c = "x";//white 50% brightness to showerror
else if (x >= 14) c = "#FFFFFF";//white full brightness
else if (x >= 12) c = "#00FF00";//green
else if (x >= 10) c = "#FF0000";//red
else if (x >= 8) c = "off";//black
else if (x >= 6) c = "yellow";
else if (x >= 4) c = "red";
else if (x >= 2) c = "green";

print(x + ":" + x % 4 + ":" + c);

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






