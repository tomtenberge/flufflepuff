/* Steering controller for flufflepuff 5.0
controls a motor to control the steering, feedback trough a potentiometer
external input trough a smoothened pwm signal from main controller
(basicly, this is a homemade servo controller)
*/
include <Servo.h>
Servo motor; // servo opbject to control motor using motor controller
int hysteria = 5; // degrees hysteria before control is send to the motor
int upper_limit = 1023; // upper limit of the turn radius
int lower_limit = 0; // lower limit of the turn radius
int motor_servo_pin = 9; // pin that is connected to the motor controller
int ext_pin = 0; // pin to the external input
int feedback_pin = 1; // pin to the senter of the feedback pot
int ext_input = 511; // signal comming from the external controller/ potmeter (0-1023) mid is off
int feedback = 511; // signal from the feedback variable resistor(0-1023)
int servo_value = 90; // signal to motor controller (value 0-180) mid is off
void setup()
{
	motor.attach(motor_servo_pin);
}

void loop()
{
	ext_input = analogRead(ext_pin); //get the requested turn radius 0-5v (0-1023, 511 is middle)
	feedback = analogRead(feedback_pin);// get the current turn radius (0-1023, 511 should be middle)
	ext_input = map(ext_input, 0,1023,lower_limit, upper_limit); // limit the action radius of the steering to the physical limits
	if (feedback < ext_input) // turn the front wheel one way
	{
		int difference = ext_input - feedback;
		difference = map(difference, 0, 1023, 0, 90);
		if (difference > hysteria)
		{
			servo_value = 90 + difference;// set speed depending on length to travel
		}
		else 
		{
			servo_value = 90;// within tolerances, do nothing
		}
	}
	else if (feedback > ext_input)// turn the front wheel the other way
	{
		int difference = feedback - ext_input;
		difference = map(difference, 0, 1023, 0, 90);
		if (difference > hysteria)
		{
			servo_value = 90 - difference;// set speed depending on length to travel
		}
		else 
		{
			servo_value = 90;// within tolerances, do nothing
		}
	}
	else // the wheel is in the correct position
	{
		servo_value = 90;
	}
	motor.write(servo_value);//write the speed to the actual motor controller.
}