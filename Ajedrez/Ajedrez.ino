#include <GBClock.h>
#include <LiquidCrystal_PCF8574.h>

#define P1 27
#define P2 16
#define P3 17

LiquidCrystal_PCF8574 lcd(0x3F); 

namespace chess
{
  struct Time
  {
  public:

    void set(int _minutes, int _seconds)
    {
      minutes = _minutes;
      seconds = _seconds;
    }

    String toString()
    {
      return "0" + String(minutes) + ":" + (seconds <= 9 ? "0" + String(seconds) : String(seconds));
    }

    void sub()
    {
      if(seconds == 0 && minutes == 0) return;

      if(seconds - 1 < 0)
      {
        minutes--;
        seconds = 60 - abs(seconds - 1);
      } 
      else seconds--;
    }

  private: 

    int minutes;
    int seconds;
  };

  struct Player
  {
  public:

    Player()
    {
      time.set(5, 0);
    }

    void restart()
    {
      time.set(5, 0);
    }

    void update()
    {
      time.sub();
    }

    Time time;
  };

}

chess::Player p1, p2;
gb::Clock ck;

void render()
{
  lcd.setCursor(0, 1);
  lcd.print(p1.time.toString() + "  ||  " + p2.time.toString());
}

bool p1pressed = false;
bool p2pressed = false;
bool p3pressed = false;

byte turn;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);

  ck.start();
  turn = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("J1     ||     J2");
  lcd.setCursor(0, 1);
  lcd.print(p1.time.toString() + "  ||  " + p2.time.toString());
}

void loop() 
{
  if(!digitalRead(P1)) p1pressed = true;
  if(!digitalRead(P2)) p2pressed = true;
  if(!digitalRead(P3)) p3pressed = true;

  if(digitalRead(P1) && p1pressed)
  {
    turn = 1;
    p1pressed = false;
  }

  if(digitalRead(P2) && p2pressed)
  {
    turn = 2;
    p2pressed = false;
  }

  if(digitalRead(P3) && p3pressed)
  {
    turn = 0;
    p1.restart();
    p2.restart();
    render();
    p3pressed = false;
  }

  if(ck.check(1000))
  {
    if(turn == 1) p1.update();
    if(turn == 2) p2.update();
    ck.restart();

    render();
  }
}
