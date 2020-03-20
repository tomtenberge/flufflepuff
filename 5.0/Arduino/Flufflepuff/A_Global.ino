//Pin assignments
//Serial 1 = Remote
//Serial 2 = Audio
#define sens_B1 A1
#define sens_B2 A2
#define sens_B3 A3
#define sens_B4 A4
#define sens_B5 A5
void init_pins()
{
	
}

//Global variables
int main_counter =0;
bool killed = false;
bool killed_man = true;
bool boosting = false;
//audio
String Audio_current_song = "";
int song_length = 0;
int song_place = 0;
byte Audio_control_1 = 0;
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


//movement
int Movement_forward = 128;
int Movement_steering = 128;

//Battery
int Battery_1 = 0;
int Battery_2 = 0;
int Battery_3 = 0;
int Battery_4 = 0;
int Battery_5 = 0;
//helpfull sniplets

struct aud_bits
{
  bool USB : 1;
  bool TF : 1;
  bool BT : 1;
  bool FX : 1;
  bool e : 1;
  bool f : 1;
  bool g : 1;
  bool h : 1;
};

union audiost
{
  byte byt = 0;
  struct aud_bits audiobits;
};
audiost Audiostatus;
