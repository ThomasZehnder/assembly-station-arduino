# assembly-station-arduino
IoT assembly station with arduino board

## Get from Git
    git clone https://github.com/ThomasZehnder/assembly-station-arduino.git

## Used Hardware ESP8266
The ESP8266 requires a 3.3V power supply. 
see https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/

![ESP8266 Pinout](/images/ESP-12E-Development-Board-ESP8266-NodeMCU-Pinout.png)

## Use PlatformIO
In VSCode see elements in the buttom left corner to transfer projekt to arduino board.

## Use Filesysten

https://randomnerdtutorials.com/esp8266-nodemcu-vs-code-platformio-littlefs/

SPIFFS is currently deprecated and may be removed in future releases of the core.

Use LittleFS instead

### Uploading Filesystem Image
After creating and saving the file or files you want to upload under the data folder, follow the next steps:

* Click the PIO icon at the left side bar. The project tasks should open.
* Select env:nodemcuv2 (it may different depending on the board you’re using).
* Expand the Platform menu.
* Select Build Filesystem Image.
* Finally, click Upload Filesystem Image.