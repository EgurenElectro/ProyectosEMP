//------------------------------------------------------------
// Programa: A07_brilloled3_pwm.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: : Igual que el programa A06 pero tres pulsadores controlan el brillo de tres leds.
//------------------------------------------------------------

#define D1 12
#define D2 13
#define D3 5

#define P1 27
#define P2 16
#define P3 17

float iD1;
float iD2;
float iD3;

void setup() 
{ 
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);

  iD1 = 0;
  iD2 = 0;
  iD3 = 0;
}

void loop() 
{
  if(!digitalRead(P1)) iD1 = iD1 == 255 ? 0 : iD1 + (255 * 0.1);
  if(!digitalRead(P2)) iD2 = iD2 == 255 ? 0 : iD2 + (255 * 0.1);
  if(!digitalRead(P3)) iD3 = iD3 == 255 ? 0 : iD3 + (255 * 0.1);

  delay(200);

  analogWrite(D1, iD1);
  analogWrite(D2, iD2);
  analogWrite(D3, iD3);
}
