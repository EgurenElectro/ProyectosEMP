// Titulo: S02_control_pasos
// Autor: Gabriel Bravo T31A

#include <ESP32Servo.h>
#include <LiquidCrystal_PCF8574.h>

#define P1 27
#define P2 16
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

GBClock clock1;
Servo servo;
LiquidCrystal_PCF8574 lcd(0x3F); 

bool p1Pressed = false;
bool p2Pressed = false;

unsigned int angle = 90;

void LCDWrite(unsigned int _angle)
{
  lcd.clear();
  lcd.home();
  lcd.print(angle);
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

  LCDWrite(angle);
  servo.write(angle);
  delay(50);
}

void loop() 
{
  if(!digitalRead(P1)) p1Pressed = true;
  if(!digitalRead(P2)) p2Pressed = true;

  if(digitalRead(P1) && p1Pressed)
  {
    p1Pressed = false;

    if(angle < 180) 
    {
      angle += 10;
      servo.write(angle);
      LCDWrite(angle);
      delay(50);
    }
  }

  if(digitalRead(P2) && p2Pressed)
  {
    p2Pressed = false;

    if(angle > 0) 
    {
      angle -= 10;
      servo.write(angle);
      LCDWrite(angle);
      delay(60);
    }
  }
}
