//------------------------------------------------------------
// Programa: D09_control_nivel.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (15-01-2025)
// Descripción: Control del encendido/apagado de los cuatro leds de la placa, según se
//              activen los pulsadores de llenado (P1) y vaciado (P2). Inicialmente el depósito está vacío (leds
//              D1,D2,D3 y D4 apagados). Si se pulsa P1 se encienden de forma consecutiva a intervalos de 100ms
//              hasta quedar todos encendidos. Si se pulsa P1 y ya está el depósito lleno parpadearán tres veces
//              todos los leds. Si se pulsa P2 se vacía el depósito apagándose los leds siguiendo la secuencia
//              D4,D3,D2 y D1 hasta quedar todos apagados.
//------------------------------------------------------------

#define P1 27
#define P2 16

#define D1 12
#define D2 13
#define D3 5
#define D4 23

bool lleno = false;

void setup() 
{
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
}

void loop() 
{
  if(!digitalRead(P2) && lleno)
  {
    digitalWrite(D4, 0);
    delay(100);
    digitalWrite(D3, 0);
    delay(100);
    digitalWrite(D2, 0);
    delay(100);
    digitalWrite(D1, 0);
    lleno = false;
  }

  if(!digitalRead(P1))
  {
    if(!lleno)
    {
      digitalWrite(D1, 1);
      delay(100);
      digitalWrite(D2, 1);
      delay(100);
      digitalWrite(D3, 1);
      delay(100);
      digitalWrite(D4, 1);
      lleno = true;
    }
    else
    {
      for(byte i = 0; i < 3; i++)
      {
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
        delay(200);
        digitalWrite(D1, 1);
        digitalWrite(D2, 1);
        digitalWrite(D3, 1);
        digitalWrite(D4, 1);
        delay(100);
      }
    }
  }
}
