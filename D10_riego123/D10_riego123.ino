//------------------------------------------------------------
// Programa: D10_riego123.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (15-01-2025)
// Descripción: Realizar un programa que simule el funcionamiento de tres bombas de riego
//              B1,B2 y B3 (leds en D1,D2 y D3) controladas por los tres pulsadores de la placa (P1,P2 y P3). Las
//              bombas solamente se pueden activar siguiendo la secuencia B1>B2>B3 y apagar en orden inverso
//              B3>B2>B1.
//------------------------------------------------------------

#define B1 12
#define B2 13
#define B3 5

#define P1 27
#define P2 16
#define P3 17

bool b1Active = false;
bool b2Active = false;
bool b3Active = false;

void setup() 
{
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);

  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(B3, OUTPUT);
}

void loop() 
{
  if(!digitalRead(P1))
  {
    if(!b1Active && !b2Active && !b3Active) b1Active = true;
    else if(b1Active && !b2Active && !b3Active) b1Active = false;

    digitalWrite(B1, b1Active);
    delay(500);
  }

  if(!digitalRead(P2))
  {
    if(b1Active && !b2Active && !b3Active) b2Active = true;
    else if(b1Active && b2Active && !b3Active) b2Active = false;

    digitalWrite(B2, b2Active);
    delay(500);
  }

  if(!digitalRead(P3))
  {
    if(b1Active && b2Active && !b3Active) b3Active = true;
    else if(b1Active && b2Active && b3Active) b3Active = false;

    digitalWrite(B3, b3Active);
    delay(500);
  }
}
