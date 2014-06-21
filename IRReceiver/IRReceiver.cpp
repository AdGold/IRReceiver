#include "IRReceiver.h"

unsigned int IRReceiver::abs2(unsigned int a, unsigned int b)
{
  if (a > b) return a-b;
  return b-a;
}

bool IRReceiver::isSuffix(unsigned int *values)
{
  if (abs2(values[0],SUFFIX0)*100/SUFFIX0 > MAXERROR) return false;
  if (abs2(values[1],SUFFIX1)*100/SUFFIX1 > MAXERROR) return false;
  if (abs2(values[2],SUFFIX2)*100/SUFFIX2 > MAXERROR) return false;
  return true;
}

bool IRReceiver::isPrefix(unsigned int *values)
{
  if (abs2(values[0],PREFIX0)*100/PREFIX0 > MAXERROR) return false;
  if (abs2(values[1],PREFIX1)*100/PREFIX1 > MAXERROR) return false;
  return true;
}

bool IRReceiver::getData(unsigned int *values, int len)
{
//  Serial.print("start test, len = ");
//  Serial.println(len);
  if (len == 3) return isSuffix(values); // resend cmd is simply sending the suffix
  if (len != 71 && len != 67) return false;
  if (!isPrefix(values)) return false;
  unsigned char bytes[4] = {0,0,0,0};
  for (int byteNum = 0; byteNum < 4; byteNum++)
  {
    for (int i = 0; i < 8; i++)
    {
      int bit = (values[byteNum*16 + 3 + i*2] > 1000);
      bytes[byteNum] |= (bit << i);
    }
  }
  if (bytes[0] != IDENTIFIER) return false;
  if (bytes[0] != bytes[1] && bytes[0] != (unsigned char)~bytes[1]) return false;
  if (bytes[2] != (unsigned char)~bytes[3]) return false;
  data = bytes[2];
  return true;//(len == 71 && isSuffix(values+68));
}

bool IRReceiver::delay(unsigned long time, unsigned char &button) //waits time ms or until a signal is received
{
  unsigned long start = millis();
  while (millis() - start < time)
  {
    if (poll(button)) return true;
  }
  return false;
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

bool IRReceiver::poll(unsigned char &button)
{
  if (digitalRead(IRPin) == LOW)
  {
    unsigned int lens[100];
    int state = digitalRead(IRPin);
    unsigned long start = micros();
    int count = 0;
    while (true)
    {
      if (digitalRead(IRPin) != state || count > 70)
      {
        if (micros() - start <= MAXLEN && micros() - start >= MINLEN)
        {
          lens[count++] = micros() - start;
        }
        else if (count)
        {
          if (getData(lens, count))
          {
            button = data;
            return true;
          }
          break;
        }
        state = !state;
        start = micros();
      }
    }
  }
  return false;
}
