//#include <PS2X_lib.h>
#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
//PS2X ps2x;
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int joy_error = 0; 
byte joy_type = 0;
boolean display_ok = false;
boolean controller_firstboot = true;
int bat_1 = 0;
int bat_2 = 0;
int bat_3 = 0;
int bat_4 = 0;
int bat_5 = 0;
int bat_6 = 0;
boolean onehanded = false;
int trottle = 128;
int steering = 128;
int audiocontrol = 0;
/*
 * 0 = nothing
 * 1 = next song
 * 2 = previous song
 * enz
 * 
 */
int fxbank = 0;
String mp3file = "-";
int Audio_volume = 10;
