//Titulo: S04_serial_servo.ino
//Autor: Gabriel Bravo Eguren

#include <ESP32Servo.h>

#define SERVO 25

//Objeto Reloj (Gabriel Bravo Clock)
struct GBClock
{
public:

  void start()
  {
    startTime = millis();
    running = true;
  }

  unsigned long stop()
  {
    running = false;
    return millis() - startTime;
  }

  unsigned long restart()
  {
    unsigned long elapsed = stop();
    start();
    return elapsed;
  }

  bool check(unsigned long mark)
  {
    if (!running) return false;
    
    return millis() - startTime >= mark;
  }

  unsigned long elapsed()
  {
    if(running) return millis() - startTime;
    else return 0;
  }

  bool started()
  {
    return running;
  }

private:

  unsigned long startTime = 0;
  bool running = false;
};


Servo servo;
GBClock ck;

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
