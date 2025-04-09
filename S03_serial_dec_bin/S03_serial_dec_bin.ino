//Titulo: S03_serial_dec_bin.ino
//Autor: Gabriel Bravo Eguren

#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F); 

void setup() 
{  
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  Serial.begin(9600);
}

String binario(int numero)
{
  String resultado = "";
  int actual = numero;

  while(actual != 0 && actual != 1)
  {
    resultado += String(actual % 2);
    actual = actual / 2;
  }

  resultado += String(actual); 

  String copia = resultado;
  resultado = "";

  for(int i = copia.length() - 1; i >= 0; i--)
  {
    resultado += String(copia.charAt(i));
  }

  return resultado;
}

void loop() 
{
  if(Serial.available())
  {
    auto valor = Serial.parseInt();

    lcd.clear();
    lcd.home();
    lcd.print(binario(valor));
  }
}
