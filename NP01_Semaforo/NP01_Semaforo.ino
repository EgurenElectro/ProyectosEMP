#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 8
#define PIN 26
#define P1 27
#define P2 16

Adafruit_NeoPixel tira = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool p1pressed = false;
unsigned long tinicio = 0;

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

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
}


void loop() 
{
  if(!digitalRead(P1)) p1pressed = true;

  while(!digitalRead(P2))
  {
    if(tinicio == 0)
    {
      tinicio = millis();
    }

    auto transcurrido = millis() - tinicio;

    if(transcurrido <= 500)
    {
      color("off");
    }
    else if(transcurrido <= 1000)
    {
      color("naranja");
    }
    else if(transcurrido > 1000)
    {
      tinicio = 0;
    }
  }

  if(digitalRead(P1) && p1pressed)
  {
    p1pressed = false;
    color("naranja");
    delay(2000);
    color("rojo");
    delay(5000);
  }

  color("verde");
}
