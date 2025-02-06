//------------------------------------------------------------
// Programa: LCD07_control_led.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A 
// Descripción: Realizar un programa para controlar el
//              estado del led bicolor entre los tres posibles: “OFF”, “Verde” o
//              “Rojo”. P1 funcionará como botón de selección de opción.
//              Moverá el asterisco por las tres opciones. El pulsador P3 será el botón de Enter que modificará el
//              estado del led bicolor.
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define P1 27
#define P3 17

#define DG 18
#define DR 19

LiquidCrystal_PCF8574 lcd(0x3F); 

bool update = true;

bool p1down = false;
bool p3down = false;

int option = -1;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(DR, OUTPUT);
  pinMode(DG, OUTPUT);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
}

void loop() 
{
  if(!digitalRead(P1)) p1down = true;
  if(!digitalRead(P3)) p3down = true;

  if(digitalRead(P1) && p1down)
  {
    if(option == 1) option = -1;
    else option++;
    
    p1down = false;
    update = true;
  }

  if(digitalRead(P3) && p3down)
  {
    if(option == -1)
    {
      digitalWrite(DG, 0);
      digitalWrite(DR, 0);
    }
    else if(option == 0) 
    {
      digitalWrite(DG, 1);
      digitalWrite(DR, 0);
    }
    else
    {
      digitalWrite(DG, 0);
      digitalWrite(DR, 1);
    }

    p3down = false;
  }

  if(update)
  {
    lcd.clear();

    lcd.setCursor(0,0);

    lcd.print("(");
    if(option == -1) lcd.print("*");
    else lcd.print(" ");
    lcd.print(")OFF");

    lcd.setCursor(0, 1);

    lcd.print("(");
    if(option == 0) lcd.print("*");
    else lcd.print(" ");
    lcd.print(")Verde (");
    if(option == 1) lcd.print("*");
    else lcd.print(" ");
    lcd.print(")Rojo");

    update = false;
  }

  delay(200);
} 
