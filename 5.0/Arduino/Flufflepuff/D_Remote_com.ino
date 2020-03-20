#include <PacketSerial.h>
PacketSerial Remote;
//Remote on serial 1
// boud rate = 9600
/* control commands:
MVFW 0-255 Movement forward/reverse 128 = movement 0
MVLR 0-255 Movement left/right 128 = straight
UNKILL = Remove kill state
KULL = Manual Kill
UNKULL = End manual Kill
KILLED = message to send killed status
KULLED = message to send killed status
BA01 0-99 = Battery capacity driving battery 1
BA02 0-99 = Battery capacity driving battery 2
BA03 0-99 = Battery capacity driving battery 3
BA04 0-99 = Battery capacity driving battery 4
BACT 0-99 = Battery capacity control battery
BOOS 0-1 = Booster active (switch batteries parallel/series
*/
/* Audio commands
AU VO 0-30 = Audio volume
AU ST AR = Start playing music
AU ST OP = Stop playing music
AU NX = Next song
AU PR = Previous song
AU FX 00 00 = play FX 1 time (last number = fx number)
AU FX 01 00 = Play FX continuously (last number = FX number)
AU FX 02 = Stop playing FX
*/

void Remote_init()
{
	Serial1.begin(9600);
  Remote.setStream(&Serial1);
  Remote.setPacketHandler(&onPacketReceived);
}
void onPacketReceived(const uint8_t* buffer, size_t size)
{
}
void senddata()
{
  int i = 0;
  bool algstatus[8] = {killed, killed_man, boosting, false, false, false, false, false};
  byte data[10 + Audio_current_song.length()];
  data[0] = Audiostatus.byt;
  //data[0] = BoolArrayToByte(audiostatus);
  //data[1] = BoolArrayToByte(algstatus);
  data[2] = Battery_1;
  data[3] = Battery_2;
  data[4] = Battery_3;
  data[5] = Battery_4;
  data[6] = Battery_5;
  //fix this int16_t to 2xint8_t
  //data[7] = song_length;
  //data[8] = song_length;
  data[9] = Audio_current_song.length();
  while ( i < Audio_current_song.length())
  {
    data[i+10] = Audio_current_song.charAt(i);
    i++;
  }
  Remote.send(data,10 + Audio_current_song.length());
}
void Remote_loop()
{
  Remote.update();
}
