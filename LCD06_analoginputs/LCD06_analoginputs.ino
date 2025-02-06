//------------------------------------------------------------
// Programa: LCD06_analoginputs.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A 
// Descripción: Realizar un programa que muestre
//              en la primera línea del LCD el valor leído de la resistencia LDR
//              de la shield (valor digital leído directamente del ADC) y en la
//              segunda línea, el valor del voltaje en el pin del potenciómetro medido en voltios.
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define POT 34
#define LDR 2

LiquidCrystal_PCF8574 lcd(0x3F); 

bool update = true;

float vpot = 0;
int vldr = 0;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);
}

void loop() 
{
  float pot = (analogRead(POT) * 3.3) / 4095;
  int ldr = analogRead(LDR);

  if(vldr != ldr) 
  {
    vldr = ldr;
    update = true;
  }

  if(vpot != pot)
  {
    vpot = pot;
    update = true;
  }


  if(update)
  {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("LDR: " + String(vldr));

    lcd.setCursor(0, 1);
    lcd.print("Pot: " + String(vpot) + " Volts");

    update = false;
  }

  delay(200);
} 
