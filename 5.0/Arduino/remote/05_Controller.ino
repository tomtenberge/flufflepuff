void controller_init()
{
  joy_error = ps2x.config_gamepad(5,4,3,2, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  if(joy_error == 0)
  {
    Serial.println("Found Controller, configured successful");
  }
  else if(joy_error == 1)
  {
    Serial.println("No controller found");
  }
  else if(joy_error == 2)
  {
    Serial.println("Controller found but not accepting commands");
  }
  else if(joy_error == 3)
  {
    Serial.println("Controller refusing to enter Pressures mode");
  }
  joy_type = ps2x.readType(); 
  switch(joy_type)
  {
    case 1:
      Serial.println("DualShock Controller Found");
      break;
  }
}
void controller_loop()
{
  if(joy_error == 1) //skip loop if no controller found
  {
    return; 
  }
  else
  {
    //DualShock Controller
    ps2x.read_gamepad(false, 0);
    if(ps2x.ButtonPressed(PSB_L2))
    {
      onehanded = true;
    }
    else if (ps2x.ButtonReleased(PSB_L2))
    {
      onehanded = false;
    }
    
    //read out the analog sticks
    if (controller_firstboot)
    {
      if ((ps2x.Analog(PSS_LY) == 255) && (ps2x.Analog(PSS_LX) == 255)
      && (ps2x.Analog(PSS_RY) == 255) && (ps2x.Analog(PSS_RX) == 255))
      {
        trottle = 128;
        steering = 128;
      }
      else
      {
        controller_firstboot = false;
      }
    }
    else
    {
      if (onehanded)
      {
        trottle = ps2x.Analog(PSS_LY);
        steering = ps2x.Analog(PSS_LX);
      }
      else
      {
        trottle = ps2x.Analog(PSS_LY);
        steering = ps2x.Analog(PSS_RX);
      }
    }
    trottle = 255-trottle;
    if(ps2x.ButtonPressed(PSB_L1))
    {
      boosting = true;
    }
    else if (ps2x.ButtonReleased(PSB_L1))
    {
      boosting = false;
    }
	  if ((!ps2x.Button(PSB_R2)) && (ps2x.Button(PSB_R1)))
	  {
      fxbank1 = false;
      fxbank2 = true;
      fxbank3 = false;
      fxbank4 = false;
	  }
    else if ((ps2x.Button(PSB_R2)) && (!ps2x.Button(PSB_R1)))
	  {
      fxbank1 = false;
      fxbank2 = false;
      fxbank3 = true;
      fxbank4 = false;
	  }
      else if ((ps2x.Button(PSB_R2)) && (ps2x.Button(PSB_R1)))
	  {
      fxbank1 = false;
      fxbank2 = false;
      fxbank3 = false;
      fxbank4 = true;
	  }
    else if ((!ps2x.Button(PSB_R2)) && (!ps2x.Button(PSB_R1)))
	  {
      fxbank1 = true;
      fxbank2 = false;
      fxbank3 = false;
      fxbank4 = false;
	  }
    if(ps2x.ButtonPressed(PSB_GREEN))
    {
      Action1 = true;
    }
    else if (ps2x.ButtonReleased(PSB_GREEN))
    {
      Action1 = false;
    }
    if(ps2x.ButtonPressed(PSB_RED))
    {
      Action2 = true;
    }
    else if (ps2x.ButtonReleased(PSB_RED))
    {
      Action2 = false;
    }
    if(ps2x.ButtonPressed(PSB_PINK))
    {
      Action3 = true;
    }
    else if (ps2x.ButtonReleased(PSB_PINK))
    {
      Action3 = false;
    }
    if(ps2x.ButtonPressed(PSB_BLUE))
    {
      Action4 = true;
    }
    else if (ps2x.ButtonReleased(PSB_BLUE))
    {
      Action4 = false;
    }
  if (ps2x.Button(PSB_PAD_UP))
  {
    Audio_volume++;
    if (Audio_volume > 30)
    {
      Audio_volume = 30;
    }
  }
  if (ps2x.Button(PSB_PAD_DOWN))
  {
    Audio_volume--;
    if (Audio_volume < 0)
    {
      Audio_volume = 0;
    }
  }
  if(ps2x.Button(PSB_PAD_LEFT))
  {
    audiocontrol = 5;
  }
  else if(ps2x.Button(PSB_PAD_RIGHT))
  {
    audiocontrol = 4;
  }
  else
  {
    audiocontrol = 0;
  }
 }
}
	//TESTING CRAP
	/* 
	
    if(ps2x.ButtonPressed(PSB_START))           //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if(ps2x.ButtonPressed(PSB_SELECT))
      Serial.println("Select is being held");
    if(ps2x.ButtonPressed(PSB_PAD_UP))         //will be TRUE as long as button is pressed
      Serial.println("Up is being held");
    if(ps2x.ButtonPressed(PSB_PAD_RIGHT))
      Serial.println("Right is being held");
    if(ps2x.ButtonPressed(PSB_PAD_LEFT))
      Serial.println("LEFT is being held");
    if(ps2x.ButtonPressed(PSB_PAD_DOWN))
      Serial.println("DOWN is being held");
    if(ps2x.ButtonPressed(PSB_L3))
      Serial.println("L3 is being held");
    if(ps2x.ButtonPressed(PSB_R3))
         Serial.println("R3 is being held");
    if(ps2x.ButtonPressed(PSB_L2))
         Serial.println("L2 is being held");
    if(ps2x.ButtonPressed(PSB_R2))
         Serial.println("R2 is being held");
    if(ps2x.ButtonPressed(PSB_GREEN))
         Serial.println("Triangle is being held");
    if(ps2x.ButtonPressed(PSB_RED))             
         Serial.println("Circle just pressed");  
    if(ps2x.ButtonPressed(PSB_PINK))
         Serial.println("Square just released");   
    if(ps2x.ButtonPressed(PSB_BLUE))
         Serial.println("X just changed");    
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC); 
    } 
  }
}*/
