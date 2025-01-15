//------------------------------------------------------------
// Programa: D06_giromotor.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (15-01-2025)
// Descripción: Realizar un programa que controle el sentido de giro de un motor controlado
//              por tres pulsadores P1=giro_IZDA, P2=Paro y P3=giroDCHA. Representar el estado del motor con
//              leds de la siguiente manera: Paro(todos OFF), IZDA(D1=D2=ON, resto OFF) y DCHA(D3=D4=ON, resto
//              OFF). Para ampliar: Evitar el cambio de giro sin pasar por paro.
//------------------------------------------------------------

#define P1 27
#define P2 16
#define P3 17

#define D1 12
#define D2 13
#define D3 5
#define D4 23

int status = 0;

void setup() 
{
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
}

void loop() 
{
  if(!digitalRead(P2)) status = 0;
  if(!digitalRead(P1) && status == 0) status = -1;
  if(!digitalRead(P3) && status == 0) status = 1;

  if(status == 0)
  {
    digitalWrite(D1, 0);
    digitalWrite(D2, 0);
    digitalWrite(D3, 0);
    digitalWrite(D4, 0);
  }
    
  if(status == -1)
  {
    digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D3, 0);
    digitalWrite(D4, 0);
  }

  if(status == 1)
  {
    digitalWrite(D1, 0);
    digitalWrite(D2, 0);
    digitalWrite(D3, 1);
    digitalWrite(D4, 1);
  }

}
