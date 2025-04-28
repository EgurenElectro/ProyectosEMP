#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 8
#define PIN 26
#define POT 34

#define P1 27
#define P2 16
#define P3 17

Adafruit_NeoPixel tira = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool p1pressed = false;
bool p2pressed = false;
bool p3pressed = false;

byte color = 0;
int r = 0;
int g = 0;
int b = 0;

void setup() 
{
  tira.begin();
  tira.setBrightness(64);
  tira.clear();

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
}

void loop() 
{
  if(!digitalRead(P1)) p1pressed = true;
  if(!digitalRead(P2)) p2pressed = true;
  if(!digitalRead(P3)) p3pressed = true;

  if(digitalRead(P1) && p1pressed) 
  {
    p1pressed = false;
    color = 0;
    g = 0;
    b = 0; 
  }

  if(digitalRead(P2) && p2pressed) 
  {
    p2pressed = false;
    color = 1;
    r = 0;
    b = 0; 
  }

  if(digitalRead(P3) && p3pressed) 
  {
    p3pressed = false;
    color = 2;
    r = 0;
    g = 0; 
  }

  if(color == 0) r = map(analogRead(POT), 0, 4095, 0, 255);
  if(color == 1) g = map(analogRead(POT), 0, 4095, 0, 255);
  if(color == 2) b = map(analogRead(POT), 0, 4095, 0, 255);

  for(int i = 0; i < 8; i++)
  {
    tira.setPixelColor(i, tira.Color(r, g, b));
    tira.show();
  }
}
