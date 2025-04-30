#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 8
#define PIN 26
#define POT 34

#define P1 27
#define P2 16

Adafruit_NeoPixel tira = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool p1pressed = false;
bool p2pressed = false;

byte color = 0;

struct RGB 
{
  RGB(unsigned int _r, unsigned int _g, unsigned int _b)
  {
    r = _r;
    g = _g;
    b = _b;
  }

  unsigned int r = 255;
  unsigned int g = 255;
  unsigned int b = 255;

  uint32_t getColor()
  {
    return tira.Color(r, g, b);
  }
};

RGB rojo(255, 0, 0);
RGB verde(0, 255, 0);
RGB azul(0, 0, 255);
RGB off(0, 0, 0);

byte codColor = 0;
int brillo = 2;

void setup() 
{
  tira.begin();
  tira.setBrightness(64);
  tira.clear();

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
}

void loop() 
{
  int pot = map(analogRead(POT), 0, 4095, -1, NUMPIXELS - 1);

  if(!digitalRead(P1)) p1pressed = true;
  if(!digitalRead(P2)) p2pressed = true;

  if(digitalRead(P1) && p1pressed) 
  {
    color = color == 0 ? 1 : color == 1 ? 2 : 0;
    p1pressed = false;
  }

  if(digitalRead(P2) && p2pressed) 
  {
    brillo = brillo == 2 ? 4 : brillo == 4 ? 6 : 2;
    p2pressed = false;
  }

  for(int i = -1; i < NUMPIXELS; i++)
  {
    if(i == -1 || i > pot) tira.setPixelColor(i, off.getColor());
    else
    {
      if(color == 0) tira.setPixelColor(i, verde.getColor());
      if(color == 1) tira.setPixelColor(i, azul.getColor());
      if(color == 2) tira.setPixelColor(i, rojo.getColor());
    }

    tira.setBrightness(map(brillo, 0, 10, 0, 100));
    tira.show();
  }
  
}
