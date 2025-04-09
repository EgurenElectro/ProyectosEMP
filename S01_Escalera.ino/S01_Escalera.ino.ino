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
bool update = true;
byte dstatus = 0;

void setup() 
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(P1, INPUT_PULLUP);

  waiter = -1000;
}

void loop() 
{
  if(!digitalRead(P1)) p1pressed = true;

  if(digitalRead(P1) && p1pressed)
  {
    p1pressed = false;
    waiter = 5000;
    t1 = millis();
    update = true;
  }

  if(waiter > 0)
  {
    waiter -= millis() - t1;
    t1 = millis();
    dstatus = 1;
  }
  else 
  {
    dstatus = 0;

    if(waiter != -1000)
    {
      update = true;
      waiter = -1000;
    }
  }

  if(update)
  {
    update = false;
    digitalWrite(D1, dstatus);
    digitalWrite(D2, dstatus);
    digitalWrite(D3, dstatus);
    digitalWrite(D4, dstatus);
  }
}
