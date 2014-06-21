#ifndef IR_RECEIVER
#define IR_RECEIVER

#include <Arduino.h>

#define MAXLEN 65000
#define MINLEN 300
#define MAXERROR 25

class IRReceiver
{
public:
  IRReceiver(int pin) { IRPin = pin; }
  void begin() { pinMode(IRPin, INPUT); }
  bool poll(unsigned char &button);
  bool delay(unsigned long time, unsigned char &button); //waits time ms or until a signal is received
private:
  bool getData(unsigned int *values, int len);
  bool isPrefix(unsigned int *values);
  bool isSuffix(unsigned int *values);
  unsigned int abs2(unsigned int a, unsigned int b);
  unsigned char data;
  int IRPin;
};

void printButton(unsigned char id);

#define IDENTIFIER 0B00011000
#define POWER 0B00001000
#define MUTE 0B00001001
#define CHANNEL_UP 0B00000000
#define VOLUME_UP 0B00000010
#define CHANNEL_DOWN 0B00000001
#define MENU 0B10110100
#define SLEEP 0B00011110
#define CHANNEL_CALL 0B00001111
#define SKIP 0B11011010
#define MOVE 0B11011011
#define DELETE 0B11011100
#define MODE 0B11011101
#define TV_VIDEO 0B00001010
#define PICTURE 0B00101000
#define ONE 0B00010000
#define TWO 0B00010001
#define THREE 0B00010010
#define FOUR 0B00010011
#define FIVE 0B00010100
#define SIX 0B00010101
#define SEVEN 0B00010110
#define EIGHT 0B00010111
#define NINE 0B00011000
#define ZERO 0B00011010
#define LINES 0B11001010
#define LINES_X 0B11010010

#define PREFIX0 9100
#define PREFIX1 4380

#define SUFFIX0 9050
#define SUFFIX1 2200
#define SUFFIX2 580

#endif //IR_RECEIVER
