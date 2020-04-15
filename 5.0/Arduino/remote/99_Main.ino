void setup()
{
  //start serial
 display_init();
 serial_init();
 battery_init();
 //get gamepad up and running
 controller_init();
}

void loop()
{
  serial_loop();
  battery_loop();
  controller_loop();
  display_loop();
  delay(50);
}
