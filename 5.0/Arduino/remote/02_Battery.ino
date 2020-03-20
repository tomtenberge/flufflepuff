void battery_init()
{
  
}
void battery_loop()
{
  float batt = analogRead(A0);
  //Serial.print(batt);
  //Serial.print("-");
  bat_1 = map(batt,0,1023,0,500);
  //Serial.print(bat_1);
  //Serial.print("-");
  if ((bat_1 < 320) || (bat_1 > 500))
  {
    bat_1 = 0;
    //Serial.println("XXX");
  }
  else
  {
    bat_1 = map(bat_1,320,500,0,7);
  }
  //Serial.println(bat_1);
}
