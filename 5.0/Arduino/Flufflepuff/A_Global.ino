/*Pin assignments
Serial = usb debug
Serial 1 = Remote
Serial 2 = Audio
pin 3 = servo gas
*/
#define serial1_command 2
#define servo_gas_pin 3
#define sens_B1 A1
#define sens_B2 A2
#define sens_B3 A3
#define sens_B4 A4
#define sens_B5 A5
#define DAC_RESOLUTION    (8)
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Servo.h>
Adafruit_MCP4725 steering;
Servo gas;
void init_pins()
{
	
}
int tmp0 = 0;
//Global variables
int main_counter =0;
bool killed = false;
bool killed_man = true;
bool boosting = false;
//audio
String Audio_current_song = "";
int song_length = 0;
int song_place = 0;
bool Audio_to_usb = false;
bool Audio_to_tf = false;
bool Audio_to_bt = false;
bool audio_start = false;
bool audio_stop = false;
bool audio_next = false;
bool audio_prev = false;
/*
0 = nothing
1 = switch to usb
2 = switch to TF
3 = switch to bt
4 = Next song
5 = Prev song
6 = Stop
7 = Play
*/
int Audio_volume = 10;// set audio volume (min 0, max 30)
bool audio_up = false;
bool audio_down = false;

//actions
boolean fxbank1 = false;
boolean fxbank2 = false;
boolean fxbank3 = false;
boolean fxbank4 = false;
boolean fxbtn1 = false;
boolean fxbtn2 = false;
boolean fxbtn3 = false;
boolean fxbtn4 = false;
boolean fxaction01 = false;
boolean fxaction02 = false;
boolean fxaction03 = false;
boolean fxaction04 = false;
boolean fxaction05 = false;
boolean fxaction06 = false;
boolean fxaction07 = false;
boolean fxaction08 = false;
boolean fxaction09 = false;
boolean fxaction10 = false;
boolean fxaction11 = false;
boolean fxaction12 = false;
boolean fxaction13 = false;
boolean fxaction14 = false;
boolean fxaction15 = false;
boolean fxaction16 = false;

//movement
int Movement_forward = 128;
int Movement_steering = 128;

//Battery
int Battery_1 = 0;
int Battery_2 = 0;
int Battery_3 = 0;
int Battery_4 = 0;
int Battery_5 = 0;

// remote
bool RemoteTimeout = false;
