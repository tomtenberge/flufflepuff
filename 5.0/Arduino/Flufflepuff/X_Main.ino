void setup() 
{
	Serial.begin(9600);
  Serial.println("Debug Started");
	init_pins();
	Remote_init();
	Audio_init();
	Movement_init();
	Battery_init();
}

void loop() 
{  
  Remote_loop();
	if ((killed != true) || (killed_man != true))
	{
		Audio_loop();
		Movement_loop();
	}
  main_counter++;
  if (main_counter > 5)
  {
    main_counter = 0;
    Battery_loop();
    senddata();
  }
}
