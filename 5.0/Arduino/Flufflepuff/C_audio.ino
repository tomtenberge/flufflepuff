//Audio on Serial 2
String Audio_serial_message = "";
void Audio_init()
{
	Serial2.begin(9600);
  delay(2);
  Serial2.println("AT+CN01");
  Serial2.println("ATBDFlufflepuff");
}

void Audio_loop()
{
	//Serial readout to Audio
	if (Serial2.available())
	{
		boolean Audio_serial_stop = false;
		byte Audio_rx_byte = 0;
		Audio_serial_message = "";
		while ( Audio_serial_stop == false)
		{
			Audio_rx_byte = Serial2.read();
			if (Audio_rx_byte == 0x0D)//if Carriage Return
			{
				if (Serial2.available())
				{
					Audio_rx_byte = Serial2.read();
					if (Audio_rx_byte == 0x0A)//if Line Feed
					{
						Audio_serial_stop = true; //stop reading and handle message
					}
				}
			}
			else
			{
				Audio_serial_message = Audio_serial_message + String(char(Audio_rx_byte));//add byte to message
			}
     if (Audio_serial_message.length() > 150)
     {
      Audio_serial_stop = true;
      Serial.println("Serial Error");
     }
		}
    Serial.println("Serial-2:" + Audio_serial_message);
	}
}
