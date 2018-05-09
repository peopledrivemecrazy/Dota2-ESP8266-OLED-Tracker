# Dota2-ESP8266-OLED-Tracker
Tracks and displays prizepool for given league id which updates every 10 seconds.

# Initial setup and instructions
The code uses https://github.com/ThingPulse/esp8266-oled-ssd1306 <br>
This library uses dota2 web api go to https://dev.dota2.com/showthread.php?t=58317 to obtain your api keys to obtain league listings you can use https://api.steampowered.com/IDOTA2Match_570/GetLeagueListing/v0001/?key=your_key 

**Edit only this code block**
```
const char* ssid = "Your WIFI";
const char* password = "Your WIFI Password";
String api = "Your API KEY";
String leagueid = "9870"; // this is TI8 id
```
# OLED Connections
| OLED 128x64 | WEMOS | 
|-------------|-------|
| VCC         | 3.3   |
| GND         | GND   |
| SDA         | D3    |
| SCL         | D4    |
