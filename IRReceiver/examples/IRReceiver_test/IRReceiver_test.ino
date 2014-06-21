#include <IRReceiver.h>

IRReceiver ir(15);

void setup()
{
  Serial.begin(9600);
  ir.begin();
}

void loop()
{
  unsigned char buttonPressed;
  if (ir.poll(buttonPressed)) printButton(buttonPressed); 
}
