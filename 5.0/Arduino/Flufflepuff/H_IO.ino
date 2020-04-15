void IO_setup()
{
  pinMode(23, OUTPUT);//rel-1 contact scoot
  pinMode(25, OUTPUT);//rel-2 booster
  pinMode(27, OUTPUT);//rel-3 toeter
  pinMode(29, OUTPUT);//rel-4 licht
  pinMode(31, OUTPUT);//rel-5
  pinMode(33, OUTPUT);//rel-6
  pinMode(35, OUTPUT);//rel-7
  pinMode(37, OUTPUT);//rel-8
  pinMode(39, OUTPUT);//rel-9
  pinMode(41, OUTPUT);//rel-10
  pinMode(43, OUTPUT);//rel-11
  pinMode(45, OUTPUT);//rel-12
  pinMode(47, OUTPUT);//rel-13
  pinMode(49, OUTPUT);//rel-14
  pinMode(51, OUTPUT);//rel-15
  steering.begin(0x60);
  gas.attach(servo_gas_pin);
  
}

void IO_loop()
{
  if (RemoteTimeout || killed_man)
  {
    steering.setVoltage(map(128,0,256,0,4096), false);
    gas.write(map(128,0,256,0,180));
    // turn everything off
    digitalWrite(23,LOW);//power scoot on
    digitalWrite(25,LOW);//boost (not working)
    digitalWrite(27,LOW);//Horn
    digitalWrite(29,LOW);//Lights
    digitalWrite(31,LOW);
    digitalWrite(33,LOW);
    digitalWrite(35,LOW);
    digitalWrite(37,LOW);
    digitalWrite(39,LOW);
    digitalWrite(41,LOW);
    digitalWrite(43,LOW);
    digitalWrite(45,LOW);
    digitalWrite(47,LOW);
    digitalWrite(49,LOW);
    digitalWrite(51,LOW);
  }
  else
  {
    digitalWrite(23,HIGH);
    steering.setVoltage(map(Movement_steering,0,256,0,4096), false);
    gas.write(map(Movement_forward,256,0,0,180));
    if (boosting)
    {
      digitalWrite(25,HIGH);
      gas.write(map(Movement_forward,256,0,0,180));
    }
    else
    {
      digitalWrite(25,LOW);
      gas.write(map(Movement_forward,256,0,45,135));
    }
	if (fxbank1)
	{
		if (fxbtn1)
		{
			if (fxaction01)
			{
				//action 1 continue
				F_fxaction01(1);
			}
			else
			{
				//action 1 new
				F_fxaction01(0);
				fxaction01 = true;
			}
		}
		else
		{
			if (fxaction01)
			{
				//action 1 end
				F_fxaction01(3);
				fxaction01 = false;
			}
			else
			{
				//action 1 wasn't there
				F_fxaction01(4);
			}
		}
		if (fxbtn2)
		{
			if (fxaction02)
			{
				//action 2 continue
				F_fxaction02(1);
			}
			else
			{
				//action 2 new
				F_fxaction02(0);
			}
		}
		else
		{
			if (fxaction02)
			{
				//action 2 end
				F_fxaction02(3);
				fxaction02 = false;
			}
			else
			{
				//action 2 wasn't there
				F_fxaction02(4);
			}
		}
		if (fxbtn3)
		{
			if (fxaction03)
			{
				//action 3 continue
				F_fxaction03(1);
			}
			else
			{
				//action 3 new
				F_fxaction03(0);
			}
		}
		else
		{
			if (fxaction03)
			{
				//action 3 end
				F_fxaction03(3);
				fxaction03 = false;
			}
			else
			{
				//action 3 wasn't there
				F_fxaction03(4);
			}
		}
		if (fxbtn4)
		{
			if (fxaction04)
			{
				//action 1 continue
				F_fxaction04(1);
			}
			else
			{
				//action 1 new
				F_fxaction04(0);
			}
		}
		else
		{
			if (fxaction04)
			{
				//action 4 end
				F_fxaction04(3);
				fxaction04 = false;
			}
			else
			{
				//action 4 wasn't there
				F_fxaction04(4);
			}
		}
		if (fxaction05)
		{
			fxaction05 = false;
			F_fxaction05(2);
		}
		else
		{
			F_fxaction05(3);
		}
		if (fxaction06)
		{
			fxaction06 = false;
			F_fxaction06(2);
		}
		else
		{
			F_fxaction06(3);
		}
		if (fxaction07)
		{
			fxaction07 = false;
			F_fxaction07(2);
		}
		else
		{
			F_fxaction07(3);
		}
		if (fxaction08)
		{
			fxaction08 = false;
			F_fxaction08(2);
		}
		else
		{
			F_fxaction08(3);
		}
		if (fxaction09)
		{
			fxaction09 = false;
			F_fxaction09(2);
		}
		else
		{
			F_fxaction09(3);
		}
		if (fxaction10)
		{
			fxaction10 = false;
			F_fxaction10(2);
		}
		else
		{
			F_fxaction10(3);
		}
		if (fxaction11)
		{
			fxaction11 = false;
			F_fxaction11(2);
		}
		else
		{
			F_fxaction11(3);
		}
		if (fxaction12)
		{
			fxaction12 = false;
			F_fxaction12(2);
		}
		else
		{
			F_fxaction12(3);
		}
		if (fxaction13)
		{
			fxaction13 = false;
			F_fxaction13(2);
		}
		else
		{
			F_fxaction13(3);
		}
		if (fxaction14)
		{
			fxaction14 = false;
			F_fxaction14(2);
		}
		else
		{
			F_fxaction14(3);
		}
		if (fxaction15)
		{
			fxaction15 = false;
			F_fxaction15(2);
		}
		else
		{
			F_fxaction15(3);
		}
		if (fxaction16)
		{
			fxaction16 = false;
			F_fxaction16(2);
		}
		else
		{
			F_fxaction16(3);
		}
	}
	else if (fxbank2)
	{
		if (fxaction01)
		{
			fxaction01 = false;
			F_fxaction01(2);
		}
		else
		{
			F_fxaction01(3);
		}
		if (fxaction02)
		{
			fxaction02 = false;
			F_fxaction02(2);
		}
		else
		{
			F_fxaction02(3);
		}
		if (fxaction03)
		{
			fxaction03 = false;
			F_fxaction03(2);
		}
		else
		{
			F_fxaction03(3);
		}
		if (fxaction04)
		{
			fxaction04 = false;
			F_fxaction04(2);
		}
		else
		{
			F_fxaction04(3);
		}
		if (fxbtn1)
		{
			if (fxaction05)
			{
				//action 5 continue
				F_fxaction05(1);
			}
			else
			{
				//action 5 new
				F_fxaction05(0);
				fxaction05 = true;
			}
		}
		else
		{
			if (fxaction05)
			{
				//action 5 end
				F_fxaction05(3);
				fxaction05 = false;
			}
			else
			{
				//action 5 wasn't there
				F_fxaction05(4);
			}
		}
		if (fxbtn2)
		{
			if (fxaction06)
			{
				//action 6 continue
				F_fxaction06(1);
			}
			else
			{
				//action 6 new
				F_fxaction06(0);
			}
		}
		else
		{
			if (fxaction06)
			{
				//action 6 end
				F_fxaction06(3);
				fxaction06 = false;
			}
			else
			{
				//action 6 wasn't there
				F_fxaction06(4);
			}
		}
		if (fxbtn3)
		{
			if (fxaction07)
			{
				//action 7 continue
				F_fxaction07(1);
			}
			else
			{
				//action 7 new
				F_fxaction07(0);
			}
		}
		else
		{
			if (fxaction07)
			{
				//action 7 end
				F_fxaction07(3);
				fxaction07 = false;
			}
			else
			{
				//action 7 wasn't there
				F_fxaction07(4);
			}
		}
		if (fxbtn4)
		{
			if (fxaction08)
			{
				//action 8 continue
				F_fxaction08(1);
			}
			else
			{
				//action 8 new
				F_fxaction08(0);
			}
		}
		else
		{
			if (fxaction08)
			{
				//action 8 end
				F_fxaction08(3);
				fxaction08 = false;
			}
			else
			{
				//action 8 wasn't there
				F_fxaction08(4);
			}
		}
		if (fxaction09)
		{
			fxaction09 = false;
			F_fxaction09(2);
		}
		else
		{
			F_fxaction09(3);
		}
		if (fxaction10)
		{
			fxaction10 = false;
			F_fxaction10(2);
		}
		else
		{
			F_fxaction10(3);
		}
		if (fxaction11)
		{
			fxaction11 = false;
			F_fxaction11(2);
		}
		else
		{
			F_fxaction11(3);
		}
		if (fxaction12)
		{
			fxaction12 = false;
			F_fxaction12(2);
		}
		else
		{
			F_fxaction12(3);
		}
		if (fxaction13)
		{
			fxaction13 = false;
			F_fxaction13(2);
		}
		else
		{
			F_fxaction13(3);
		}
		if (fxaction14)
		{
			fxaction14 = false;
			F_fxaction14(2);
		}
		else
		{
			F_fxaction14(3);
		}
		if (fxaction15)
		{
			fxaction15 = false;
			F_fxaction15(2);
		}
		else
		{
			F_fxaction15(3);
		}
		if (fxaction16)
		{
			fxaction16 = false;
			F_fxaction16(2);
		}
		else
		{
			F_fxaction16(3);
		}
	}
	else if (fxbank3)
	{
		if (fxaction01)
		{
			fxaction01 = false;
			F_fxaction01(2);
		}
		else
		{
			F_fxaction01(3);
		}
		if (fxaction02)
		{
			fxaction02 = false;
			F_fxaction02(2);
		}
		else
		{
			F_fxaction02(3);
		}
		if (fxaction03)
		{
			fxaction03 = false;
			F_fxaction03(2);
		}
		else
		{
			F_fxaction03(3);
		}
		if (fxaction04)
		{
			fxaction04 = false;
			F_fxaction04(2);
		}
		else
		{
			F_fxaction04(3);
		}
		if (fxaction05)
		{
			fxaction05 = false;
			F_fxaction05(2);
		}
		else
		{
			F_fxaction05(3);
		}
		if (fxaction06)
		{
			fxaction06 = false;
			F_fxaction06(2);
		}
		else
		{
			F_fxaction06(3);
		}
		if (fxaction07)
		{
			fxaction07 = false;
			F_fxaction07(2);
		}
		else
		{
			F_fxaction07(3);
		}
		if (fxaction08)
		{
			fxaction08 = false;
			F_fxaction08(2);
		}
		else
		{
			F_fxaction08(3);
		}
		if (fxbtn1)
		{
			if (fxaction09)
			{
				//action 5 continue
				F_fxaction09(1);
			}
			else
			{
				//action 5 new
				F_fxaction09(0);
				fxaction09 = true;
			}
		}
		else
		{
			if (fxaction09)
			{
				//action 5 end
				F_fxaction09(3);
				fxaction09 = false;
			}
			else
			{
				//action 5 wasn't there
				F_fxaction09(4);
			}
		}
		if (fxbtn2)
		{
			if (fxaction10)
			{
				//action 6 continue
				F_fxaction10(1);
			}
			else
			{
				//action 6 new
				F_fxaction10(0);
			}
		}
		else
		{
			if (fxaction10)
			{
				//action 6 end
				F_fxaction10(3);
				fxaction10 = false;
			}
			else
			{
				//action 6 wasn't there
				F_fxaction10(4);
			}
		}
		if (fxbtn3)
		{
			if (fxaction11)
			{
				//action 7 continue
				F_fxaction11(1);
			}
			else
			{
				//action 7 new
				F_fxaction11(0);
			}
		}
		else
		{
			if (fxaction11)
			{
				//action 7 end
				F_fxaction11(3);
				fxaction11 = false;
			}
			else
			{
				//action 7 wasn't there
				F_fxaction11(4);
			}
		}
		if (fxbtn4)
		{
			if (fxaction12)
			{
				//action 8 continue
				F_fxaction12(1);
			}
			else
			{
				//action 8 new
				F_fxaction12(0);
			}
		}
		else
		{
			if (fxaction12)
			{
				//action 8 end
				F_fxaction12(3);
				fxaction12 = false;
			}
			else
			{
				//action 8 wasn't there
				F_fxaction12(4);
			}
		}
		if (fxaction13)
		{
			fxaction13 = false;
			F_fxaction13(2);
		}
		else
		{
			F_fxaction13(3);
		}
		if (fxaction14)
		{
			fxaction14 = false;
			F_fxaction14(2);
		}
		else
		{
			F_fxaction14(3);
		}
		if (fxaction15)
		{
			fxaction15 = false;
			F_fxaction15(2);
		}
		else
		{
			F_fxaction15(3);
		}
		if (fxaction16)
		{
			fxaction16 = false;
			F_fxaction16(2);
		}
		else
		{
			F_fxaction16(3);
		}
	}
	else if (fxbank4)
	{
		if (fxaction01)
		{
			fxaction01 = false;
			F_fxaction01(2);
		}
		else
		{
			F_fxaction01(3);
		}
		if (fxaction02)
		{
			fxaction02 = false;
			F_fxaction02(2);
		}
		else
		{
			F_fxaction02(3);
		}
		if (fxaction03)
		{
			fxaction03 = false;
			F_fxaction03(2);
		}
		else
		{
			F_fxaction03(3);
		}
		if (fxaction04)
		{
			fxaction04 = false;
			F_fxaction04(2);
		}
		else
		{
			F_fxaction04(3);
		}
		if (fxaction05)
		{
			fxaction05 = false;
			F_fxaction05(2);
		}
		else
		{
			F_fxaction05(3);
		}
		if (fxaction06)
		{
			fxaction06 = false;
			F_fxaction06(2);
		}
		else
		{
			F_fxaction06(3);
		}
		if (fxaction07)
		{
			fxaction07 = false;
			F_fxaction07(2);
		}
		else
		{
			F_fxaction07(3);
		}
		if (fxaction08)
		{
			fxaction08 = false;
			F_fxaction08(2);
		}
		else
		{
			F_fxaction08(3);
		}
		if (fxaction09)
		{
			fxaction09 = false;
			F_fxaction09(2);
		}
		else
		{
			F_fxaction09(3);
		}
		if (fxaction10)
		{
			fxaction10 = false;
			F_fxaction10(2);
		}
		else
		{
			F_fxaction10(3);
		}
		if (fxaction11)
		{
			fxaction11 = false;
			F_fxaction11(2);
		}
		else
		{
			F_fxaction11(3);
		}
		if (fxaction12)
		{
			fxaction12 = false;
			F_fxaction12(2);
		}
		else
		{
			F_fxaction12(3);
		}
		if (fxbtn1)
		{
			if (fxaction13)
			{
				//action 5 continue
				F_fxaction13(1);
			}
			else
			{
				//action 5 new
				F_fxaction13(0);
				fxaction13 = true;
			}
		}
		else
		{
			if (fxaction13)
			{
				//action 5 end
				F_fxaction13(3);
				fxaction13 = false;
			}
			else
			{
				//action 5 wasn't there
				F_fxaction13(4);
			}
		}
		if (fxbtn2)
		{
			if (fxaction14)
			{
				//action 6 continue
				F_fxaction14(1);
			}
			else
			{
				//action 6 new
				F_fxaction14(0);
			}
		}
		else
		{
			if (fxaction14)
			{
				//action 6 end
				F_fxaction14(3);
				fxaction14 = false;
			}
			else
			{
				//action 6 wasn't there
				F_fxaction14(4);
			}
		}
		if (fxbtn3)
		{
			if (fxaction15)
			{
				//action 7 continue
				F_fxaction15(1);
			}
			else
			{
				//action 7 new
				F_fxaction15(0);
			}
		}
		else
		{
			if (fxaction15)
			{
				//action 7 end
				F_fxaction15(3);
				fxaction15 = false;
			}
			else
			{
				//action 7 wasn't there
				F_fxaction15(4);
			}
		}
		if (fxbtn4)
		{
			if (fxaction16)
			{
				//action 8 continue
				F_fxaction16(1);
			}
			else
			{
				//action 8 new
				F_fxaction16(0);
			}
		}
		else
		{
			if (fxaction16)
			{
				//action 8 end
				F_fxaction16(3);
				fxaction16 = false;
			}
			else
			{
				//action 8 wasn't there
				F_fxaction16(4);
			}
		}
	}
  }
}
void F_fxaction01(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction02(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction03(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction04(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction05(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction06(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction07(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction08(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction09(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction10(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction11(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction12(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction13(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction14(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction15(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
void F_fxaction16(int state)
{
	switch(state)
	{
		case 0:
		//press button
		break;
		case 1:
		//hold button
		break;
		case 2:
		//release button
		break;
		case 3:
		//unpushed button
		break;
	}
}
