#define DEBUG

void serial_debug_init()
{
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Debug Started");
  #endif
}
void serial_debug_loop()
{
  #ifdef DEBUG
  if (RemoteTimeout)
  {
    Serial.println("No remote :(");
  }
  else
  {
    
  }
  #endif
}
