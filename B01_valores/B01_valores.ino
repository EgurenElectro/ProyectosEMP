//------------------------------------------------------------
// Programa: B01_valores.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: Realiza un programa que muestre en el lcd los números del 1 al 7 separados por
//              comas en la primera línea del LCD cada vez que se pulse P1. Al pulsar P2 se borrará la pantalla.
//              Utiliza un bucle for o while para resolver el ejercicio
//------------------------------------------------------------

#define P1 27
#define P2 16

bool update = true;
byte limite = 1;

void setup() 
{
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() 
{
  if(!digitalRead(P1) && limite < 7)
  {
    limite++;
    update = true;
  }

  if(!digitalRead(P2))
  {
    for(int i = 0; i < 30; i++) Serial.println();
  }

  if(update)
  {
    for(byte i = 1; i <= limite; i++)
    {
      Serial.printf("%d", i);
      if(i != limite) Serial.print(", ");
      else Serial.println();
    }

    update = false;
  }

  delay(200);
}
