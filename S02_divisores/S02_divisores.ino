//Titulo: S02_Divisores.ino
//Autor: Gabriel Bravo Eguren

#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F); 

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available())
  {
    auto value = Serial.parseInt();

    if(value < 0 || value > 100) return;

    String divisores = "";

    for(int i = 1; i <= value; i++)
    {
      if(value % i == 0) divisores += String(i) + ",";
    }

    lcd.clear();
    lcd.home();

    if(divisores.length() <= 16)
    {
      lcd.print(divisores);
    }
    else
    {
      lcd.print(divisores.substring(0, 15));
      lcd.setCursor(0, 1);
      lcd.print(divisores.substring(16, divisores.length()));
    }
  }
}
