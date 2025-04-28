#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 8
#define PIN 26
#define POT 34

Adafruit_NeoPixel tira = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void color(String _color)
{
  if(_color == "rojo")
  {
    for(int i = 0; i < 8; i++)
    {
      tira.setPixelColor(i, tira.Color(255, 0, 0));
      tira.show();
    }
  }

  if(_color == "verde")
  {
    for(int i = 0; i < 8; i++)
    {
      tira.setPixelColor(i, tira.Color(0, 255, 0));
      tira.show();
    }
  }

  if(_color == "naranja")
  {
    for(int i = 0; i < 8; i++)
    {
      tira.setPixelColor(i, tira.Color(255, 128, 0));
      tira.show();
    }
  }

  if(_color == "off")
  {
    for(int i = 0; i < 8; i++)
    {
      tira.setPixelColor(i, tira.Color(0, 0, 0));
      tira.show();
    }
  }
}

void setup() 
{
  tira.begin();
  tira.setBrightness(64);
  tira.clear();
}

void loop() 
{
  int pot = analogRead(POT);

  if(pot <= 1360) color("verde");
  else if(pot <= 2720) color("naranja");
  else if(pot <= 4095) color("rojo");

}
