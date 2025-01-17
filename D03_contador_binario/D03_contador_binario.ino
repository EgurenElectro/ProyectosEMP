//------------------------------------------------------------
// Programa: D03_contador_binario.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: Mostrar un contador binario de 0 a 15 en los cuatro leds de la placa de
//              forma ininterrumpida
//------------------------------------------------------------

#define D1 12
#define D2 13
#define D3 5
#define D4 23

#define P1 27

#define WT 500

int tabla[16][4] = {
  {0, 0, 0, 0},
  {0, 0, 0, 1},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 1, 0, 0},
  {0, 1, 0, 1},
  {0, 1, 1, 0},
  {0, 1, 1, 1},
  {1, 0, 0, 0},
  {1, 0, 0, 1},
  {1, 0, 1, 0},
  {1, 0, 1, 1},
  {1, 1, 0, 0},
  {1, 1, 0, 1},
  {1, 1, 1, 0},
  {1, 1, 1, 1},
};

int cursor = -1;

void setup() 
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(P1, INPUT_PULLUP);
}

void loop() 
{
  if(!digitalRead(P1)) return;

  cursor = cursor == 15 ? 0 : cursor + 1;

  digitalWrite(D1, tabla[cursor][0]);
  digitalWrite(D2, tabla[cursor][1]);
  digitalWrite(D3, tabla[cursor][2]);
  digitalWrite(D4, tabla[cursor][3]);

  delay(WT);
}
