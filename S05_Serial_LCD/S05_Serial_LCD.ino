//Titulo: S05_Serial_LCD.ino
//Autor: Gabriel Bravo Eguren - T31A

/*
Realiza un programa que lea el texto recibido en el puerto serie
y lo muestre en el lcd. Si se envía la cadena “$t” se debe apagar/encender la
retroiluminación de la pantalla y la cadena “$c” borrará la pantalla y pondrá el cursor
en la posición 0,0
*/

#include <LiquidCrystal_PCF8574.h>


LiquidCrystal_PCF8574 lcd(0x3F); 

bool lcdON = true;


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
    String mensaje = Serial.readString();

    if(mensaje[0] == '$')
    {
      if(mensaje[1] == 't') 
      {
        lcd.setBacklight(lcdON ? 0 : 255);
        lcdON = !lcdON;
      } 

      if(mensaje[1] == 'c')
      {
        lcd.clear();
        lcd.home();
      }
    }
    else
    {
      lcd.clear();
      lcd.home();

      if(mensaje.length() > 16)
      {
        lcd.print(mensaje.substring(0, 15));
        lcd.setCursor(0, 1);
        lcd.print(mensaje.substring(16, mensaje.length()));
      }
      else lcd.print(mensaje);
    }
  }
}
