void Battery_init()
{
	
}
void Battery_loop()
{
	Battery_1 = analogRead(sens_B1);
	Battery_2 = analogRead(sens_B2);
	Battery_3 = analogRead(sens_B3);
	Battery_4 = analogRead(sens_B4);
	Battery_5 = analogRead(sens_B5);
	Battery_1 = map(Battery_1, 0, 1023, 0, 141);
	Battery_2 = map(Battery_2, 0, 1023, 0, 282);
	Battery_3 = map(Battery_3, 0, 1023, 0, 423);
	Battery_4 = map(Battery_4, 0, 1023, 0, 564);
	Battery_5 = map(Battery_5, 0, 1023, 0, 141);
	Battery_4 = Battery_4 - Battery_3;
	Battery_3 = Battery_3 - Battery_2;
	Battery_2 = Battery_2 - Battery_1;
	
}
