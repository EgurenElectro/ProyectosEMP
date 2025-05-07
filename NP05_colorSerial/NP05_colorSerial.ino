#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 8
#define PIN 26

Adafruit_NeoPixel tira = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

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

RGB colorActual = off;

void setup() 
{
  tira.begin();
  tira.setBrightness(64);
  tira.clear();

  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available())
  {
    String entrada = Serial.readString();
    entrada.toLowerCase();

    if(entrada.charAt(0) == '$') 
    {
      auto brillo = entrada.substring(1, entrada.length()).toInt();
      Serial.println(brillo);
      brillo = map(brillo, 0, 100, 0, 255);
      tira.setBrightness(brillo);
      tira.show();
    } 
    if(entrada == "rojo") colorActual = rojo;
    else if(entrada == "verde") colorActual = verde;
    else if(entrada == "azul") colorActual = azul;
  }

  for(int i = 0; i < NUMPIXELS; i++)
  {
    tira.setPixelColor(i, colorActual.getColor());
    tira.show();
  }
}
