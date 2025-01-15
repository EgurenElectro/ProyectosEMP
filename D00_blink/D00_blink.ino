//------------------------------------------------------------
// Programa: D00_blink.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: Parpadeo led rojo de la shield cada segundo
//------------------------------------------------------------

#define DR 19

void setup() 
{
  pinMode(DR, OUTPUT);

}

void loop() 
{
  digitalWrite(DR, HIGH);
  delay(1000);
  digitalWrite(DR, LOW);
  delay(1000);
}
