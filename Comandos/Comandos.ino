#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F); 

unsigned int backlight = 255;


void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(backlight);


  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available())
  {
    String input = Serial.readString();

    Serial.println(input);

    if(input.charAt(0) != '$')
    {
      String text = input;

      if(text.length() > 16)
      {
        lcd.clear();
        lcd.home();
        lcd.print(text.substring(0, 15));
        lcd.setCursor(0, 1);
        lcd.print(text.substring(16, text.length()));
      }
      else
      {
        lcd.clear();
        lcd.home();
        lcd.print(text);
      }
    }
    else                    
    {
      switch(input.charAt(1))
      {
        case 't': backlight = backlight == 255 ? 0 : 255; break;
        case 'b': lcd.clear(); break;
      }
    }
  }

  lcd.setBacklight(backlight);
}
