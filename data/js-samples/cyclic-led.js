// java script cyclic
//print('CYCLIC from File LEd Demo');

  
  x=(x+1);
  if (x>=20){
    EspClearLed();
    x=0;
  } 
  var c ="on";//white
  if (x>=2) c= "green";
  if (x>=4) c= "red";
  if (x>=6) c= "yellow";
  if (x>=8) c= "off";//black
  if (x>=10) c= "#FF0000";//red
  if (x>=12) c= "#00FF00";//green
  if (x>=14) c= "#FFFFFF";//white full brightness
  if (x>=16) c= "x";//white 50% brightness to showerror
  print(x);
  EspSetLed(x%4,c);
  