//------------------------------------------------------------
// Programa: A08_pulsa3_blink.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: Realizar un programa que controle el parpadeo del led D1 con tres pulsadores.
//              P1 genera un parpadeo de 2Hz, P2 de 4Hz y P3 de 8Hz.
//------------------------------------------------------------

#define D1 12

#define P1 27
#define P2 16
#define P3 17

int periodoP1;
int periodoP2;
int periodoP3;

byte opcion;

void setup() 
{
  pinMode(D1, OUTPUT);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);

  periodoP1 = 1000 / 2;
  periodoP2 = 1000 / 4;
  periodoP3 = 1000 / 8;

  opcion = 0;
}

void loop() 
{
  if(!digitalRead(P1)) opcion = 0;
  if(!digitalRead(P2)) opcion = 1;
  if(!digitalRead(P3)) opcion = 2;

  digitalWrite(D1, HIGH);

  if(opcion == 0) delay(periodoP1 / 2);
  if(opcion == 1) delay(periodoP2 / 2);
  if(opcion == 2) delay(periodoP3 / 2);

  digitalWrite(D1, LOW);

  if(opcion == 0) delay(periodoP1 / 2);
  if(opcion == 1) delay(periodoP2 / 2);
  if(opcion == 2) delay(periodoP3 / 2);
}
