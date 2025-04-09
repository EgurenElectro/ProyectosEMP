//Titulo: S04_serial_servo.ino
//Autor: Gabriel Bravo Eguren

#include <ESP32Servo.h>
#include <GBClock.h>

#define SERVO 25

Servo servo;
gb::Clock ck;

int actual = 0;
int diferencia = 0;

void setup() 
{
  ESP32PWM::allocateTimer(0); 
  servo.setPeriodHertz(50); 
  servo.attach(SERVO, 600, 2400);

  Serial.begin(9600); 
  servo.write(actual);
}

void loop() 
{
  if(Serial.available() && !ck.started())
  {
    auto leido = Serial.parseInt();
    diferencia = abs(actual - leido);

    if(leido >= 0 && leido <= 180)
    {
      servo.write(leido);
      actual = leido;
      ck.start();
    }
  }

  if(ck.started())
  {
    if(ck.check(diferencia)) ck.stop();
  }
}
