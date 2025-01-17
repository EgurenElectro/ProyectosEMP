//------------------------------------------------------------
// Programa: A02_contador_pot.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: Realiza un programa para conseguir un contador binario de 0 a 15 (0000 –
//              1111) controlado con el potenciómetro en los leds de la shield de periféricos. Utiliza la estructura
//              if..else para resolver el ejercicio.
//------------------------------------------------------------

#define D1 12
#define D2 13
#define D3 5
#define D4 23

#define POT 34

int potValue;

byte binTable[16][4] = {
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,0,1,1},
  {0,1,0,0},
  {0,1,0,1},
  {0,1,1,0},
  {0,1,1,1},  
  {1,0,0,0},
  {1,0,0,1},
  {1,0,1,0},
  {1,0,1,1},
  {1,1,0,0},
  {1,1,0,1},
  {1,1,1,0},
  {1,1,1,1}
};

void setup() 
{
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D1, OUTPUT);

}

void displayNum(byte num)
{
  digitalWrite(D1, binTable[num][0]);
  digitalWrite(D2, binTable[num][1]);
  digitalWrite(D3, binTable[num][2]);
  digitalWrite(D4, binTable[num][3]);
}

void loop() 
{
  potValue = map(analogRead(POT), 0, 4095, 0, 100);

  for(byte i = 0; i < 16; i++)
  {
    if(potValue == (100/16) * (i+1)) displayNum(i);
  }

}
