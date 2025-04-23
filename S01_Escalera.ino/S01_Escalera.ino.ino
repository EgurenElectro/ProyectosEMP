//Titulo: S01_Escalera.ino
//Autor: Gabriel Bravo Eguren - T31A

#define D1 12
#define D2 13
#define D3 5
#define D4 23

#define P1 27

unsigned long t1;
long waiter;

bool p1pressed = false;
byte d1status = 0;
byte d2status = 0;
byte d3status = 0;
byte d4status = 0;

void setup() 
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(P1, INPUT_PULLUP);

  waiter = 0;
}

void loop() 
{
  if(!digitalRead(P1)) p1pressed = true;

  if(digitalRead(P1) && p1pressed)
  {
    p1pressed = false;
    waiter = 5000;
    t1 = millis();
  }

  if(waiter > 0)
  {
    waiter -= millis() - t1;
    t1 = millis();
    
    if(waiter <= 5000) d1status = 1;
    if(waiter <= 4900) d2status = 1;
    if(waiter <= 4800) d3status = 1;
    if(waiter <= 4700) d4status = 1;
  }
  else 
  {
    d1status = 0;
    d2status = 0;
    d3status = 0;
    d4status = 0;
  }

  digitalWrite(D1, d1status);
  digitalWrite(D2, d2status);
  digitalWrite(D3, d3status);
  digitalWrite(D4, d4status);
}
