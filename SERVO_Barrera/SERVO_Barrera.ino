#include <ESP32Servo.h>
#include <LiquidCrystal_PCF8574.h>
#include <GBClock.h>

#define P1 27
#define SERVO 25
#define DV 18
#define DR 19

#define ON 1
#define OFF 0
#define WT 180

Servo servo1; 
LiquidCrystal_PCF8574 lcd(0x3F); 
gb::Clock _clock;

struct Input 
{
  
}

bool moving = false;
bool p1down = false;
int angle = 90;

void status(byte code)
{ 
  lcd.clear();
  lcd.home();

  if(code == 0)
  {
    digitalWrite(DV, 1);
    digitalWrite(DR, 0);
    lcd.print("Moviendo: OFF");
  }
  else
  {
    digitalWrite(DV, 0);
    digitalWrite(DR, 1);
    lcd.print("Moviendo: ON");
    lcd.setCursor(0, 1);
    lcd.print("Espere");
  }

}

void setup() 
{
  ESP32PWM::allocateTimer(0); 
  servo1.setPeriodHertz(50); 
  servo1.attach(SERVO, 600, 2400); 

  lcd.begin(16, 2);
  lcd.setBacklight(255);
  
  pinMode(P1, INPUT_PULLUP);
  pinMode(DV, OUTPUT);
  pinMode(DR, OUTPUT);
  
  moving = true;
  status(ON);
  servo1.write(90);
  delay(WT);
  status(OFF);
  moving = false;

  Serial.begin(9600);
}

void loop() 
{
  if(!digitalRead(P1) && !moving) p1down = true;

  if(digitalRead(P1) && p1down && !moving)
  {
    if(angle == 0) angle = 90;
    else angle = 0;

    servo1.write(angle);
    _clock.start();
    status(ON);

    moving = true;
    p1down = false;
  }

  if(moving && _clock.check(WT))
  {
    status(OFF);
    moving = false;
  }
}