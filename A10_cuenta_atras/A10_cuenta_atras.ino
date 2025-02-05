//------------------------------------------------------------
// Programa: A10_cuenta_atras.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción:  Modifica el programa contador para conseguir un temporizador de 0 a 15
//               segundos. El potenciómetro controla el tiempo en segundos que se mostrará en binario en los leds
//               de la shield y al pulsar P1 comenzará una cuenta atrás en los leds cada segundo hasta llegar a cero,
//               momento en el cual sonarán 4 pitidos cortos en el buzzer. 
//------------------------------------------------------------

#define POT 34
#define P1 27

#define D1 12
#define D2 13
#define D3 5
#define D4 23

#define BUZ 14

byte tabla[16][4] = {
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
  {1, 1, 1, 1}
};

int waitTime = 1000;

int limit = 16;

void setup() 
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(BUZ, OUTPUT);
  pinMode(P1, INPUT_PULLUP);
}

void loop() 
{
  limit = map(analogRead(POT), 0, 4095, 0, 15);

  if(!digitalRead(P1))
  {
    for(int i = limit; i >= 0; i--)
    {
      digitalWrite(D1, tabla[i][0]);
      digitalWrite(D2, tabla[i][1]);
      digitalWrite(D3, tabla[i][2]);
      digitalWrite(D4, tabla[i][3]);
      delay(waitTime);
    }

    for(byte i = 0; i < 4; i++)
    {
      analogWrite(BUZ, 128);
      delay(150);
      analogWrite(BUZ, 0);
      delay(150);
    }
  }
  else
  {
    digitalWrite(D1, tabla[limit][0]);
    digitalWrite(D2, tabla[limit][1]);
    digitalWrite(D3, tabla[limit][2]);
    digitalWrite(D4, tabla[limit][3]);
  }

  delay(16);
}
