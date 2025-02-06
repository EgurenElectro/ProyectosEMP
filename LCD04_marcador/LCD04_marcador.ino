//------------------------------------------------------------
// Programa: LCD04_marcador.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A 
// Descripción: Realizar un programa que muestre un
//              marcador en las dos líneas del LCD. “Local: 0” y “Visit: 0 ”. P1
//              incrementa el marcador y P2 lo decrementa (no puede ser
//              inferior a cero). Si P3 está pulsado P1 y P2 controlan el marcador visitante y si no está pulsado
//              controlarán el marcador local.
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define P1 27
#define P2 16
#define P3 17

LiquidCrystal_PCF8574 lcd(0x3F); 

int local = 0;
int visitante = 0;
bool update = true;

bool p1down = false;
bool p2down = false;

byte mode = 0;

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
  if(!digitalRead(P1)) p1down = true;
  if(!digitalRead(P2)) p2down = true;

  if(!digitalRead(P3)) mode = 1;
  else mode = 0;

  if(mode == 0)
  {
    if(digitalRead(P1) && p1down)
    { 
      local++;
      update = true;
      p1down = false;
    }
    if(digitalRead(P2) && p2down)
    {
      local = local > 0 ? local - 1 : local;
      update = true;
      p2down = false;
    }
  }

  if(mode == 1)
  {
    if(digitalRead(P1) && p1down) 
    {
      visitante++;
      update = true;
      p1down = false;
    }
    if(digitalRead(P2) && p2down)
    {
      visitante = visitante > 0 ? visitante - 1 : visitante;
      update = true;
      p2down = false;
    }
  }

  if(update)
  {
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Local: " + String(local));
    lcd.setCursor(0, 1);
    lcd.print("Visitante: " + String(visitante));

    update = false;
  }
} 
