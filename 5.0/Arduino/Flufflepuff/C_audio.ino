//Audio on Serial 2
String Audio_serial_message = "";
#define Audio_select_BT AT+CM01\r\n
#define Audio_select_USB AT+CM02\r\n
#define Audio_select_SD AT+CM03\r\n
void Audio_init()
{
	Serial2.begin(9600);
	Serial2.print("AT+CT05\r\n");//set bitrate to 115200
	Serial2.begin(19200);
	Serial2.print("AT+CT05\r\n");//set bitrate to 115200
	Serial2.begin(38400);
	Serial2.print("AT+CT05\r\n");//set bitrate to 115200
	Serial2.begin(57600);
	Serial2.print("AT+CT05\r\n");//set bitrate to 115200
	Serial2.begin(256000);
	Serial2.print("AT+CT05\r\n");//set bitrate to 115200
	Serial2.begin(115200);
	Serial2.print("AT+CT05\r\n");//set bitrate to 115200
	delay(2);
	Serial2.print("AT+CN01\r\n");// mute beeps
	Serial2.print("AT+BDFluffle\r\n");//set bluetooth name
	Serial2.print("AT+BEHenk\r\n");//set bluetooth password
	Serial2.print("AT+BMFluffle\r\n");//set bluetooth low power-name
	Serial2.print("AT+CP01\r\n");//do nothing at all, select no mode
	Serial2.print("AT+CK00\r\n");//do nothing at all, select no mode
	Serial2.print("AT+CJ00\r\n");//do nothing at all, select no mode
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
