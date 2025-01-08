//Programa: parpadeo.ino (placa esp32 + shield)
//Autor: Gabriel Bravo Eguren - Enero 2025

#define PLED 12

void setup() 
{
  pinMode(PLED, OUTPUT);

}

void loop() 
{
  digitalWrite(PLED, HIGH);
  delay(1000);
  digitalWrite(PLED, LOW);
  delay(1000);

}
