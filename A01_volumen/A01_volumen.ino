//------------------------------------------------------------
// Programa: A01_volumen.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: Realiza un programa para controlar el número de leds encendidos de la shield
//              de periféricos (D1, D2, D3 y D4) en función del valor leído en el potenciómetro. Utiliza la estructura
//              if..else para resolver el ejercicio.
//------------------------------------------------------------

#define D1 12
#define D2 13
#define D3 5
#define D4 23

#define POT 34

int potValue = 0;

void setup() 
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);


}

void loop() 
{
  potValue = map(analogRead(POT), 0, 4095, 0, 100);

  if(potValue == 0)
  {
    digitalWrite(D1, 0);
    digitalWrite(D2, 0);
    digitalWrite(D3, 0);
    digitalWrite(D4, 0);
  }
  else if(potValue <= 25)
  {
    digitalWrite(D1, 1);
    digitalWrite(D2, 0);
    digitalWrite(D3, 0);
    digitalWrite(D4, 0);
  }
  else if(potValue <= 50)
  {
    digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D3, 0);
    digitalWrite(D4, 0);
  }
  else if(potValue <= 75)
  {
    digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D3, 1);
    digitalWrite(D4, 0);
  }
  else
  {
    digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D3, 1);
    digitalWrite(D4, 1);
  }


}
