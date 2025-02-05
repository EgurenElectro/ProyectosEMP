//------------------------------------------------------------
// Programa: D02_intermitente.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: : Generar una secuencia de intermitente a la derecha en los cuatro leds de
//                la placa de forma que se vayan encendiendo de forma consecutiva según la secuencia D1,D2,D3 y
//                D4 a intervalos de 50ms. Después se apagarán todos los leds durante 1seg. y se volverá a repetir la
//                secuencia (tres veces en total).
//------------------------------------------------------------

#define D1 12
#define D2 13
#define D3 5
#define D4 23

#define INTERVALO 100

void setup() 
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
}

void loop() 
{
  for(byte i = 0; i < 3; i++)
  {
    digitalWrite(D1, HIGH);
    delay(INTERVALO);
    
    digitalWrite(D2, HIGH);
    delay(INTERVALO);
      
    digitalWrite(D3, HIGH);
    delay(INTERVALO);
        
    digitalWrite(D4, HIGH);
    delay(INTERVALO);

    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    delay(INTERVALO);

    delay(1000);
  }
}
