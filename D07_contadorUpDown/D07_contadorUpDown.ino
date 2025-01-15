//------------------------------------------------------------
// Programa: D07_contadorUpDown.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (15-01-2025)
// Descripción: Utilizar los pulsadores de la placa P1(incrementar), P2(reset) y
//              P3(decrementar) para conseguir un contador bcd ascendente/descendente de 0-9 en los leds de la
//              placa.
//------------------------------------------------------------

#define P1 27
#define P2 16
#define P3 17

#define D1 12
#define D2 13
#define D3 5
#define D4 23

byte num = 0;

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

void getBCD(byte num, byte* bcd)
{
  bcd[0] = num == 1 ? 1 : 0;
  bcd[1] = 0;
  bcd[2] = 0;
  bcd[3] = 0;

  byte posCont = 0;

  while((num / 2) > 0)
  {
    bcd[posCont] = num % 2;
    num = num / 2;
    posCont++;

    if(num == 1) 
    {
      bcd[posCont] = 1;
      break;
    }
  }

}

void loop() 
{
  if(!digitalRead(P1) && num < 9) num++;
  if(!digitalRead(P2)) num = 0; 
  if(!digitalRead(P3) && num > 0) num--; 

  byte bcd[4];
  getBCD(num, bcd);

  
  digitalWrite(D4, bcd[0]);
  digitalWrite(D3, bcd[1]);
  digitalWrite(D2, bcd[2]);
  digitalWrite(D1, bcd[3]);

  delay(200);
}
