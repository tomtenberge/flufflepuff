void setup() 
{
  serial_debug_init();
	init_pins();
	Remote_init();
	Audio_init();
	Movement_init();
	Battery_init();
  IO_setup();
}

void loop() 
{  
  serial_debug_loop();
  Remote_loop();
	if ((killed != true) || (killed_man != true))
	{
		Audio_loop();
		Movement_loop();
    IO_loop();
	}
  main_counter++;
  if (main_counter > 5)
  {
    main_counter = 0;
    Battery_loop();
  }
}
