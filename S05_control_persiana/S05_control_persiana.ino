// Titulo: S05_Control_persiana.ino
// Autor: Gabriel Bravo Eguren T31A
// Fecha: 3/4/2025

#include <ESP32Servo.h>
#include <LiquidCrystal_PCF8574.h>
#include <GBClock.h>

#define SERVO 25
#define LDR 2

Servo servo;
LiquidCrystal_PCF8574 lcd(0x3F);
gb::Clock clock1;

int grados;
int prevGrados;
int ldr;

void mostrar(int ldr, int persiana)
{
  lcd.setCursor(5, 0);
  lcd.print(ldr);

  for(int i = 0; i < 11 - String(ldr).length(); i++) lcd.print(" ");

  lcd.setCursor(10, 1);
  lcd.print(persiana);

  for(int i = 10 + String(ldr).length(); i < 16; i++)
  {
    if(i == 10 + String(ldr).length()) lcd.print((char)223);
    else lcd.print(" ");
  }
  
}

void setup() 
{
  ESP32PWM::allocateTimer(0); 
  servo.setPeriodHertz(50); 
  servo.attach(SERVO, 600, 2400); 

  lcd.begin(16, 2);
  lcd.setBacklight(255);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LDR:");
  lcd.setCursor(0, 1);
  lcd.print("Persiana:");

  clock1.start();
}

void loop() 
{
  //Tasa de refresco de 50 Hz
  if(clock1.check(1/50))
  {
    ldr = analogRead(LDR);
    grados = map(ldr, 0, 4095, 180, 0);

    mostrar(ldr, grados);

    if(abs(prevGrados - grados) > 5)
    {
      servo.write(grados);
      prevGrados = grados;
    }

    clock1.restart();
  }
}
