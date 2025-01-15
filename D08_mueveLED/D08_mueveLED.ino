//------------------------------------------------------------
// Programa: D08_mueveLED.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (15-01-2025)
// Descripción: : Realizar un programa que desplace un led de derecha a izquierda con los
//                pulsadores P1 y P2. Inicialmente el led se encuentra en el lado izquierdo (D1=0n). Si se pulsa P2 el
//                led se debe “desplazar” a la derecha a intervalos de 100ms. Si ahora se pulsa P1 el led se desplazará
//                a la izquierda de la misma manera a intervalos de 100ms. Si el led se encuentra a la izda y se pulsa
//                P1 o si se encuentra en el lado derecho y se pulsa P2 no debe producirse ningún desplazamiento
//------------------------------------------------------------

#define P1 27
#define P2 16

#define D1 12
#define D2 13
#define D3 5
#define D4 23

byte pos;

void setup() 
{
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pos = 1;
  digitalWrite(D1, 1);
}


void loop() 
{
  if(!digitalRead(P2) && pos == 1)
  {
    digitalWrite(D1, 0);
    digitalWrite(D2, 1);
    delay(100);

    digitalWrite(D2, 0);
    digitalWrite(D3, 1);
    delay(100);

    digitalWrite(D3, 0);
    digitalWrite(D4, 1);
    pos = 0;
  }

  if(!digitalRead(P1) && pos == 0)
  {
    digitalWrite(D4, 0);
    digitalWrite(D3, 1);
    delay(100);

    digitalWrite(D3, 0);
    digitalWrite(D2, 1);
    delay(100);

    digitalWrite(D2, 0);
    digitalWrite(D1, 1);
    pos = 1;
  }
}
