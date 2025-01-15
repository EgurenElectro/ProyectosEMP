//------------------------------------------------------------
// Programa: D01_rafagas.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: genera en el led rojo de la Shield de
//              forma ininterrumpida, tres parpadeos de 
//              50ms seguidas de un retardo de 2seg
//------------------------------------------------------------

#define DR 19

void setup() 
{
  pinMode(DR, OUTPUT);

}

void loop() 
{
  digitalWrite(DR, HIGH);
  delay(50);
  digitalWrite(DR, LOW);
  delay(50);

  digitalWrite(DR, HIGH);
  delay(50);
  digitalWrite(DR, LOW);
  delay(50);

  digitalWrite(DR, HIGH);
  delay(50);
  digitalWrite(DR, LOW);
  delay(50);

  delay(2000);

}
