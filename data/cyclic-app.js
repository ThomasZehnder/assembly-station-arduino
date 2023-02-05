// java script cyclic
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

//fom Math package 

print("sin of " + r + "=" + Math.sin(r));