// Titulo: S03_control_pot
// Autor: Gabriel Bravo T31A

#include <ESP32Servo.h>

#define POT 34
#define SERVO 25

Servo servo;

int potValue;
int prevPotValue;

void setup() 
{
  ESP32PWM::allocateTimer(0); 
  servo.setPeriodHertz(50); 
  servo.attach(SERVO, 600, 2400);

  servo.write(90);
  delay(180);
  prevPotValue = 90;
}

void loop() 
{
  potValue = map(analogRead(POT), 0, 4095, 180, 0);

  if(prevPotValue != potValue)
  {
    servo.write(potValue);
    delay(3 * abs(potValue - prevPotValue));
    prevPotValue = potValue;
  }
}
