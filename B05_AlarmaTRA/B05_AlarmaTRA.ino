//------------------------------------------------------------
// Programa: B05_AlarmaTRA.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (15-01-2025)
// Descripción: Realiza un programa que muestre el valor de temperatura en pantalla como
//              lectura del potenciómetro. Ajustar la medida de 0 a 100ºC. Si la temperatura sube de 75 grados se
//              debe generar un tren de pitidos continuos de 1468Hz durante 50ms seguidos de una pausa de otros 50ms.
//              Para ampliar: Conseguir además que el valor de temperatura parpadee cada 500ms si es >75ºC
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define POT 34
#define BUZZER 14

LiquidCrystal_PCF8574 lcd(0x3F); 

int frec = 1468;
int temp = 0;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  lcd.setCursor(0,0);
}

void loop() 
{
  temp = map(analogRead(POT), 0, 4095, 0, 100);

  if(temp >= 75)
  {
    tone(BUZZER, frec);
    delay(50);
    noTone(BUZZER);
  }

  lcd.clear();
  lcd.print(temp);
  lcd.write(0xDF);  
  delay(50);
}
