//------------------------------------------------------------
// Programa: LCD03_turno.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A 
// Descripción: Realiza un programa para controlar el turno
//              de 0 a 99 con tres pulsadores. P1 incrementa turno, P2 lo
//              decrementa y P3 lo pone a cero. Nota: El turno pasa de 99 a 0
//              al incrementar y de 0 a 99 al decrementar.
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define P1 27
#define P2 16
#define P3 17

LiquidCrystal_PCF8574 lcd(0x3F); 

int turno = 0;
bool update = true;

bool p1Down = false;
bool p2Down = false;
bool p3Down = false;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
}

void loop() 
{
  if(!digitalRead(P1)) p1Down = true;
  if(!digitalRead(P2)) p2Down = true;
  if(!digitalRead(P3)) p3Down = true;

  if(p1Down && digitalRead(P1))
  {
    turno = turno == 99 ? 0 : turno + 1;
    p1Down = false;
    update = true;
  }

  if(p2Down && digitalRead(P2))
  {
    turno = turno == 0 ? 99 : turno - 1;
    p2Down = false;
    update = true;
  }

  if(p3Down && digitalRead(P3))
  {
    turno = 0;
    update = true;
    p3Down = false;
  }

  if(update)
  {
    lcd.clear();
    lcd.setCursor(0, 0);

    lcd.print("Su turno: " + String(turno));

    update = false;
  }
} 
