//------------------------------------------------------------
// Programa: D05_jueces.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: Realizar un programa que controle un semáforo de carreras (Rojo/Verde) con tres
//              pulsadores (P1,P2,P3). Inicialmente pulsadores en reposo y semáforo en Verde. Cuando se pulsen,
//              dos o más pulsadores, se enciende el semáforo Rojo, mientras se mantengan pulsados, y se
//              enciende el semáforo Verde en los demás casos. 
//------------------------------------------------------------

#define RED 19
#define GREEN 18

#define P1 27
#define P2 16
#define P3 17

void setup() 
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
}

bool p1_pressed = false;
bool p2_pressed = false;
bool p3_pressed = false;

void loop() 
{
  p1_pressed = !(digitalRead(P1));
  p2_pressed = !(digitalRead(P2));
  p3_pressed = !(digitalRead(P3));

  bool activate = int(p1_pressed) + int(p2_pressed) + int(p3_pressed) >= 2;

  if(activate)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
  }
  else
  {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
  }

}
