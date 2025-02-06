//------------------------------------------------------------
// Programa: LCD02_estaciones.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A 
// Descripción: Realiza un programa que muestre en
//              pantalla inicialmente en la primera línea del lcd el texto
//              “Primavera”. Cada vez que se pulse P1 (al soltar), cambiará el
//              texto por “Verano” -> ”Otoño” ->“Invierno” de forma consecutiva y cíclica.
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define P1 27

LiquidCrystal_PCF8574 lcd(0x3F); 

byte estacion = 0;
bool update = true;

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
    if(estacion == 3) estacion = 0;
    else estacion++;
    update = true;
  }

  if(update)
  {
    lcd.clear();
    lcd.setCursor(0, 0);

    if(estacion == 0) lcd.print("Primavera");
    if(estacion == 1) lcd.print("Verano");
    if(estacion == 2) 
    {
      lcd.print("Oto");
      lcd.write(0xEE);
      lcd.print("o");
    }
    if(estacion == 3) lcd.print("Invierno");

    update = false;
  }

  delay(200);
} 
