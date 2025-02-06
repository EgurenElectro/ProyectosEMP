//------------------------------------------------------------
// Programa: LCD01_mensajes.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A 
// Descripción: Realiza un programa que muestre en
//              pantalla inicialmente el mensaje “Que tenga un buen día” y al
//              pulsar P1 se cambie por “Gracias por su visita” durante 3seg y
//              luego vuelva a mostrar el mensaje inicial.
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define P1 27

LiquidCrystal_PCF8574 lcd(0x3F); 

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  
  lcd.setCursor(0, 0);
  lcd.print("Que tenga un");
  lcd.setCursor(0, 1);
  lcd.print("buen dia.");

  pinMode(P1, INPUT_PULLUP);
}

void loop() 
{
  if(!digitalRead(P1))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gracias por");
    lcd.setCursor(0, 1);
    lcd.print("su visita.");

    delay(3000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Que tenga un");
    lcd.setCursor(0, 1);
    lcd.print("buen dia.");
  }

  delay(100);
} 
