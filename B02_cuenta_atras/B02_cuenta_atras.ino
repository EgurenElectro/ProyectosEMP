//------------------------------------------------------------
// Programa: B02_cuenta-atras.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (15-01-2025)
// Descripción: Realiza un programa que muestre en el LCD el valor 10. Cuando se pulse P1
//              el valor comenzará a descontarse a intervalos de un segundo hasta llegar a cero. En este momento
//              sonarán cuatro pitidos y se reinicia el contador a 10
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define P1 27
#define P2 16
#define BUZZER 14

bool p1down = false;
bool p2down = false;

LiquidCrystal_PCF8574 lcd(0x3F); 

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);

  lcd.setCursor(0,0);
  lcd.print("10");
}

void loop() 
{
  if(!digitalRead(P1)) p1down = true;
  if(!digitalRead(P2)) p2down = true;

  if(digitalRead(P1) && p1down)
  {
    for(int i = 10; i >= 0; i--)
    {
      lcd.clear();
      lcd.print(i);
      delay(800);
    }

    for(int i = 0; i < 4; i++)
    {
      tone(BUZZER, 1047, 50); 
      delay(100);
    }

    lcd.clear();
    lcd.print("10");

    p1down = false;
  }

}
