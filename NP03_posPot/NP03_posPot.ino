#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 8
#define PIN 26
#define POT 34

Adafruit_NeoPixel tira = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  tira.begin();
  tira.setBrightness(64);
  tira.clear();
}

void loop() 
{
  int pot = map(analogRead(POT), 0, 4095, 0, NUMPIXELS - 1);

  for(int i = 0; i < NUMPIXELS; i++)
  {
    if(i == pot) tira.setPixelColor(i, tira.Color(255,0,0));
    else tira.setPixelColor(i, tira.Color(0,0,0));
    tira.show();
  }
} 
