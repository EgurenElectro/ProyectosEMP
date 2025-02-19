//------------------------------------------------------------
// Programa: B03_frecuencias.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (15-01-2025)
// Descripción: Realizar un programa que, al mantener pulsado P1, emita un pitido de 50ms
//              cada segundo de frecuencia variable de 500Hz a 2000Hz seleccionada con el potenciómetro. El valor
//              de la frecuencia seleccionada se debe mostrar en el display. Usar la función map() para ajustar la
//              escala
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define P1 27
#define BUZZER 14
#define POT 34

LiquidCrystal_PCF8574 lcd(0x3F); 

int frec = 500;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(P1, INPUT_PULLUP);
  lcd.setCursor(0,0);
  lcd.print("--Hz");
}

void loop() 
{
  int frec = map(analogRead(POT), 0, 4095, 500, 2000);
  lcd.clear();
  lcd.printf("%dHz", frec);

  if(!digitalRead(P1))
  {
    tone(BUZZER, frec, 5);
  }

  delay(5);
  
}
