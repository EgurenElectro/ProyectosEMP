//------------------------------------------------------------
// Programa: LCD09_moving_msg1.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A 
// Descripción: Realiza un programa que muestre el
//              mensaje “<EMP>” en la línea superior derecha del LCD. Cada
//              vez que se pulse P1 el texto se desplazará de izquierda a
//              derecha y volverá a su posición inicial a intervalos de 100ms. El movimiento se repite cada vez que
//              se pulse P1.
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define P1 27

LiquidCrystal_PCF8574 lcd(0x3F); 

bool p1down = false;
int pos = 0;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(P1, INPUT_PULLUP);
  update();
}

void update()
{
  lcd.clear();
  lcd.setCursor(pos, 0);
  lcd.print("<EMP>");
  delay(100);
}

void loop() 
{
  if(!digitalRead(P1)) p1down = true;

  if(digitalRead(P1) && p1down)
  {
    p1down = false;
    for(int i = 0; i < 12; i++)
    {
      pos = i;
      update();
    }

    for(int i = 11; i >= 0; i--)
    {
      pos = i;
      update();
    }
  }
} 
