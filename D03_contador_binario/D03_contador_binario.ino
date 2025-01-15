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

#define WT 1000

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
  for(byte i = 0; i < 16; i++)
  {
    if(!digitalRead(P1))
    {
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);
      break;
    }

    digitalWrite(D1, tabla[i][0]);
    digitalWrite(D2, tabla[i][1]);
    digitalWrite(D3, tabla[i][2]);
    digitalWrite(D4, tabla[i][3]);

    delay(WT);
  }

}
