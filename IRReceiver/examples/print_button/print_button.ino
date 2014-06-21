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
  if (ir.poll(buttonPressed))
  {
    printButton(buttonPressed);
  }
}

void printButton(unsigned char id)
{
  if (id == POWER) Serial.println("POWER button");
  else if (id == MUTE) Serial.println("MUTE button");
  else if (id == CHANNEL_UP) Serial.println("CHANNEL_UP button");
  else if (id == VOLUME_UP) Serial.println("VOLUME_UP button");
  else if (id == CHANNEL_DOWN) Serial.println("CHANNEL_DOWN button");
  else if (id == MENU) Serial.println("MENU button");
  else if (id == SLEEP) Serial.println("SLEEP button");
  else if (id == CHANNEL_CALL) Serial.println("CHANNEL_CALL button");
  else if (id == SKIP) Serial.println("SKIP button");
  else if (id == MOVE) Serial.println("MOVE button");
  else if (id == DELETE) Serial.println("DELETE button");
  else if (id == MODE) Serial.println("MODE button");
  else if (id == TV_VIDEO) Serial.println("TV_VIDEO button");
  else if (id == PICTURE) Serial.println("PICTURE button");
  else if (id == ONE) Serial.println("ONE button");
  else if (id == TWO) Serial.println("TWO button");
  else if (id == THREE) Serial.println("THREE button");
  else if (id == FOUR) Serial.println("FOUR button");
  else if (id == FIVE) Serial.println("FIVE button");
  else if (id == SIX) Serial.println("SIX button");
  else if (id == SEVEN) Serial.println("SEVEN button");
  else if (id == EIGHT) Serial.println("EIGHT button");
  else if (id == NINE) Serial.println("NINE button");
  else if (id == ZERO) Serial.println("ZERO button");
  else if (id == LINES) Serial.println("LINES button");
  else if (id == LINES_X) Serial.println("LINES_X button");
}
