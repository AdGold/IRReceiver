#include <IRReceiver.h>

#define CLOCK 10
#define LATCH 11
#define DATA 12

IRReceiver ir(15);

void setup()
{
  Serial.begin(9600);
  ir.begin();
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
}
byte leds = 0;
void loop()
{
  long t = millis();
  while (millis() - t < 100)
  {
    unsigned char buttonPressed;
    if (ir.poll(buttonPressed))
    {
      printButton(buttonPressed);
      int n = 0;
      switch (buttonPressed)
      {
        case ONE:n = 0;break;
        case TWO:n = 1;break;
        case THREE:n = 2;break;
        case FOUR:n = 3;break;
        case FIVE:n = 4;break;
        case SIX:n = 5;break;
        case SEVEN:n = 6;break;
        case EIGHT:n = 7;break;
        default:n = -1; break;
      }
      if (n == -1) continue;
      if (leds&(1<<n)) leds &= ~(1<<n);
      else leds |= (1<<n);
      Serial.println(leds);
    }
  }
  led(leds);
}

void led(int n)
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, n);
  digitalWrite(LATCH, HIGH);
}
