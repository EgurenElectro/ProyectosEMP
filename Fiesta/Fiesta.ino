#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel tira = Adafruit_NeoPixel(8, 26, NEO_RGB + NEO_KHZ800);

void setup() 
{
  tira.begin();
  tira.setBrightness(64);
  tira.clear();
}

void loop()
{
  for(int i = 0; i < 8; i++)
  {
    int r = random(0, 51);
    int b = random(0, 51);
    int g = random(0, 51);

    tira.setPixelColor(i, tira.Color(r, g, b));
    tira.show();
    delay(30);
  }
}
