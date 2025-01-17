//------------------------------------------------------------
// Programa: A04_analog_blink.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: Realizar un programa que controle la velocidad del parpadeo del led verde
//              de la shield (0 a 20 veces por segundo) con el potenciómetro. 
//------------------------------------------------------------

#define DG 18
#define POT 34

int periodo;
int frecuencia;

void setup() 
{
  pinMode(DG, OUTPUT);
}

void loop() 
{
  frecuencia = map(analogRead(POT), 0, 4095, 0, 20);
  periodo = 1000 / frecuencia;

  digitalWrite(DG, 1);
  delay(periodo / 2);
  digitalWrite(DG, 0);
  delay(periodo / 2);
}
