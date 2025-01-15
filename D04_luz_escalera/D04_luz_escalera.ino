//------------------------------------------------------------
// Programa: D04_luz_escalera.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: simula el funcionamiento de un alumbrado de
//              escalera. Inicialmente D1,D2,D3,D4 apagados y P1 en reposo. Cada vez que se pulse P1 se iluminan
//              todos los leds durante 5 segundos y luego se apagan. El proceso se repite cada vez que se pulsa P1.
//              Para ampliar: hacer que la secuencia de encendido sea D1,D2,D3,D4 a intervalos de 80ms y la de
//              apagado D4,D3,D2,D1 con otros 80ms de retardo
//------------------------------------------------------------

#define D1 12
#define D2 13
#define D3 5
#define D4 23

#define P1 27

void setup() 
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(P1, INPUT_PULLUP);

  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}

void loop() 
{
  if(!digitalRead(P1))
  {
    digitalWrite(D1, HIGH);
    delay(80);
    digitalWrite(D2, HIGH);
    delay(80);
    digitalWrite(D3, HIGH);
    delay(80);
    digitalWrite(D4, HIGH);

    delay(5000);

    digitalWrite(D4, LOW);
    delay(80);
    digitalWrite(D3, LOW);
    delay(80);
    digitalWrite(D2, LOW);
    delay(80);
    digitalWrite(D1, LOW);    
  }

}
