//Programa: intermitente.ino (placa esp32 + shield)
//Autor: Gabriel Bravo Eguren - Enero 2025

#define D1 12
#define D2 13
#define D3 5
#define D4 23

#define DELAY 100


void setup() 
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

}

void loop() 
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);

  delay(DELAY);

  digitalWrite(D1, HIGH);

  delay(DELAY);

  digitalWrite(D2, HIGH);


  delay(DELAY);

  digitalWrite(D3, HIGH);

  delay(DELAY);

  digitalWrite(D4, HIGH);

}
