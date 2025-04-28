#include <Adafruit_NeoPixel.h>
#include <GBClock.h>

#define NUMPIXELS 8
#define PIN 26
#define P1 27
#define P2 16

Adafruit_NeoPixel tira = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

gb::Clock ck;

bool p1pressed = false;
bool p2pressed = false;

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

  if(!digitalRead(P2)) 
  {
    p2pressed = true;
    if(!ck.started()) ck.start();

    color("off");

    if(ck.check(1000)) 
    {
      color("off");
      ck.restart();
    }
    
    if(ck.check(500)) 
    {
      color("naranja");
    }
  }

  if(digitalRead(P1) && p1pressed && !ck.started())
  {
    p1pressed = false;
    color("naranja");
    delay(2000);
    color("rojo");
    delay(5000);
  }

  if(digitalRead(P2) && p2pressed)
  {
    p2pressed = false;
    ck.stop();
  }

  if(!ck.started()) color("verde");
}
