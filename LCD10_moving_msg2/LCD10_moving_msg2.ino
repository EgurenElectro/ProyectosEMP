//------------------------------------------------------------
// Programa: LCD10_moving_msg2.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A 
// Descripción: Realiza un programa que muestre el
//              mensaje “P1->Start” centrado en la primera línea del LCD. Al
//              pulsar se mostrará el mensaje: “Proxima estación ATOCHA”,
//              entrando por la parte derecha del lcd hasta desaparecer por la
//              izquierda. Se esperará un segundo y se volverá a mostrar el
//              mensaje inicial.
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define P1 27

LiquidCrystal_PCF8574 lcd(0x3F); 

bool p1down = false;
bool update = true;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(P1, INPUT_PULLUP);
}

void loop() 
{
  if(!digitalRead(P1)) p1down = true;

  if(digitalRead(P1) && p1down)
  {
    String texto = "Proxima estacion ATOCHA";

    for(int i = 15; i >= 0; i--)
    {
      lcd.clear();
      lcd.setCursor(i, 0);
      lcd.print(texto);
      delay(250);
    }
    
    int longTexto = texto.length();

    for(int i = 0; i < longTexto; i++)
    {
      lcd.clear();
      texto = texto.substring(1);
      lcd.print(texto);
      delay(250);
    }

    delay(750);

    update = true;
    p1down = false;
  }

  if(update)
  {
    lcd.setCursor(9, 0);
    lcd.clear();
    lcd.print("P1->Start");
    update = false;
  }
}
