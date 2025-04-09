// Titulo: S01_control_pulsadores
// Autor: Gabriel Bravo Eguren T31A 

#include <ESP32Servo.h>
#include <LiquidCrystal_PCF8574.h>

#define P1 27
#define P2 16
#define P3 17

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

enum Movement
{
  LEFT, RIGHT, CENTER
};

Servo servo;
LiquidCrystal_PCF8574 lcd(0x3F); 

GBClock clock1;

bool p1Pressed = false;
bool p2Pressed = false;
bool p3Pressed = false;
bool moving = false;

void LCDWrite(String text)
{
  lcd.clear();
  lcd.home();
  lcd.print(text);
}

void move(Movement mov)
{
  clock1.start();
  moving = true;

  if(mov == LEFT) 
  {
    servo.write(180);
    LCDWrite("IZQUIERDA");
  }
  if(mov == RIGHT) 
  {
    servo.write(0);
    LCDWrite("DERECHA");
  }
  if(mov == CENTER) 
  {
    servo.write(90);
    LCDWrite("CENTRO");
  }
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
  pinMode(P3, INPUT_PULLUP);

  servo.write(90);
  delay(250);
  LCDWrite("CENTRO");
}

void loop() 
{
  if(!digitalRead(P1)) p1Pressed = true;
  if(!digitalRead(P2)) p2Pressed = true;
  if(!digitalRead(P3)) p3Pressed = true;

  if(digitalRead(P1) && p1Pressed)
  {
    p1Pressed = false;
    if(!moving) move(LEFT);
  }

  if(digitalRead(P2) && p2Pressed)
  {
    p2Pressed = false;
    if(!moving) move(CENTER);
  }

  if(digitalRead(P3) && p3Pressed)
  {
    p3Pressed = false;
    if(!moving) move(RIGHT);
  }

  if(moving && clock1.elapsed() >= 250)
  {
    clock1.stop();
    moving = false;
  }

}