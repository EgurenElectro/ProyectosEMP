// Titulo: S04_barrera_parking
// Autor: Gabriel Bravo Eguren T31A

#include <ESP32Servo.h>
#include <LiquidCrystal_PCF8574.h>
#include <GBClock.h>

#define P1 27
#define P2 16

#define SERVO 25

Servo servo;
LiquidCrystal_PCF8574 lcd(0x3F);

gb::Clock clockP1; 
gb::Clock clockP2;

int plazas = 0;

bool p1Pressed = false;
bool p2Pressed = false;

void mensaje(String texto)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(texto);
  lcd.setCursor(0, 1);
  lcd.printf("Libres: %d", 20 - plazas);
}

void setup() 
{
  ESP32PWM::allocateTimer(0); 
  servo.setPeriodHertz(50); 
  servo.attach(SERVO, 600, 2400); 

  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);

  mensaje("CERRADA");
  servo.write(0);
  delay(2000);

  f1.setup(10);
  f2.setup(10);

  Serial.begin(9600);
}

void loop() 
{
  if(!digitalRead(P1)) p1Pressed = true;
  if(!digitalRead(P2)) p2Pressed = true;

  if(digitalRead(P1) && p1Pressed)
  {
    p1Pressed = false;

    if(plazas > 0 && !clockP1.started()) 
    {
      plazas--;
      mensaje("ABIERTA");
      clockP1.start();
      servo.write(90);  
    }
  }

  if(digitalRead(P2) && p2Pressed)
  {
    p2Pressed = false;

    if(plazas < 20 && !clockP2.started())
    {
      plazas++;
      mensaje("ABIERTA");
      clockP2.start();
      servo.write(90);
    }
  }

  if(clockP1.started() && clockP1.check(2000))
  {
    servo.write(0);
    mensaje("CERRADA");
    clockP1.stop();
  }

  if(clockP2.started() && clockP2.check(2000))
  {
    servo.write(0);
    mensaje("CERRADA");
    clockP2.stop();
  }
}
