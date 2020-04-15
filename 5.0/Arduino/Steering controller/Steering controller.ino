/* Steering controller for flufflepuff 5.0
controls a motor to control the steering, feedback trough a potentiometer
external input trough a smoothened pwm signal from main controller
(basicly, this is a homemade servo controller)
*/
#include <Servo.h>
Servo motor; // servo opbject to control motor using motor controller
int hysteria = 10; // degrees hysteria before control is send to the motor
int upper_limit = 600; // upper limit of the turn radius
int lower_limit = 350; // lower limit of the turn radius
int motor_servo_pin = 9; // pin that is connected to the motor controller
int ext_pin = 0; // pin to the external input
int feedback_pin = 0; // pin to the senter of the feedback pot
int ext_input = 511; // signal comming from the external controller/ potmeter (0-1023) mid is off
int feedback = 511; // signal from the feedback variable resistor(0-1023)
int servo_value = 90; // signal to motor controller (value 0-180) mid is off
void setup()
{
  motor.attach(motor_servo_pin);
  Serial.begin(9600);
}

void loop()
{
  ext_input = analogRead(ext_pin); //get the requested turn radius 0-5v (0-1023, 511 is middle)
  feedback = analogRead(feedback_pin);// get the current turn radius (0-1023, 511 should be middle)
  ext_input = map(ext_input, 0,1023,lower_limit, upper_limit); // limit the action radius of the steering to the physical limits
  Serial.print("ext: ");
  Serial.print(ext_input);
  Serial.print(" fb : ");
  Serial.print(feedback);
  if (feedback < ext_input) // turn the front wheel one way
  {
    int difference = ext_input - feedback;
    Serial.print(" diff : ");
    Serial.print(difference);
    if (difference > hysteria)
    {
      digitalWrite(13,HIGH);
      servo_value = 180;// set speed depending on length to travel
    }
    else 
    {
      digitalWrite(13,LOW);
      servo_value = 90;// within tolerances, do nothing
    }
  }
  else if (feedback > ext_input)// turn the front wheel the other way
  {
    int difference = feedback - ext_input;
    Serial.print(" diff : ");
    Serial.print(difference);
    if (difference > hysteria)
    {
      digitalWrite(13,HIGH);
      servo_value = 0;// set speed depending on length to travel
    }
    else 
    {
      digitalWrite(13,LOW);
      servo_value = 90;// within tolerances, do nothing
    }
  }
  else // the wheel is in the correct position
  {
    digitalWrite(13,LOW);
    servo_value = 90;
  }
  Serial.print(" Servo: ");
  Serial.print(servo_value);
  Serial.println();
  motor.write(servo_value);//write the speed to the actual motor controller.
}
