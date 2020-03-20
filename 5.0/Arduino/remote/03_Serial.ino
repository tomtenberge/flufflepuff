#include <PacketSerial.h>
PacketSerial mySerial;
void serial_init()
{
  //Serial.begin(9600);
  //Serial.println("Controller booted");
  mySerial.begin(9600);
  mySerial.setPacketHandler(&onPacketReceived);
}
void serial_loop()
{
  //if (Serial.available())
  //{
  //}
  //Serial.print("data:");
  //Serial.print(Audio_volume);
  //Serial.print("|");
  //Serial.print(audiocontrol);
  //Serial.print("|");
  //Serial.print(trottle);
  //Serial.print("|");
  //Serial.print(steering);
  //Serial.println("");
}
void onPacketReceived(const uint8_t* buffer, size_t size)
{
  bat_1 = buffer[2];
  bat_2 = buffer[3];
  bat_3 = buffer[4];
  bat_4 = buffer[5];
  bat_5 = buffer[6];
}
