#include <GBClock.h>
#include <LiquidCrystal_PCF8574.h>

#define P1 27
#define P2 17

LiquidCrystal_PCF8574 lcd(0x3F);

//Clase tiempo, sirve para administrar y manejar de forma cómoda los tiempos de los jugadores.
namespace chess
{
  struct Time
  {
  public:

    Time()
    {
      minutes = 5;
      seconds = 0;
    }

    void set(int _minutes, int _seconds)
    {
      minutes = _minutes;
      seconds = _seconds;
    }

    String toString()
    {
      return (minutes <= 9 ? "0" + String(minutes) : String(minutes)) + ":" + (seconds <= 9 ? "0" + String(seconds) : String(seconds));
    }

    int getMinutes()
    {
      return minutes;
    }

    int getSeconds()
    {
      return seconds;
    }

    bool isZero()
    {
      return minutes == 0 && seconds == 0;
    }

    void add(int _minutes, int _seconds)
    {
      if(_minutes < 0  || _seconds < 0) return;
      if(_seconds > 59) return;
      if(minutes + _minutes >= 100) return;

      if(seconds + _seconds > 59)
      {
        if(minutes + 1 == 100) return;
        minutes++;
        seconds = abs(_seconds + seconds - 60);
      } 
      else seconds += _seconds;

      minutes += _minutes;
    }

    void sub(int _minutes, int _seconds)
    {
      if(_minutes < 0  || _seconds < 0) return;
      if(seconds == 0 && minutes == 0) return;
      if(minutes - _minutes < 0) return;
      if(_seconds > 59) return;

      if(seconds - _seconds < 0)
      {
        minutes--;
        seconds = 60 - abs(seconds - _seconds);
      } 
      else seconds -= _seconds;

      minutes -= _minutes;
    }

  private: 

    int minutes;
    int seconds;
  };
}

//Enumeración con las distintas pantallas disponibles para renderizar.
enum Screen 
{
  WELCOME,
  MENU,
  SETTINGS,
  CLOCK
};

//Colección de caracteres personalizados para LCD

#define SETTINGS_CHAR byte(0)
byte settingsChar[] = {
  B00000,
  B10101,
  B01110,
  B11011,
  B11011,
  B01110,
  B10101,
  B00000
};

#define TOWER_CHAR byte(1)
byte TOWERChar[] = {
  B10101,
  B11111,
  B01110,
  B01110,
  B01110,
  B11111,
  B11111,
  B00000
};

#define CLOCK_CHAR byte(2)
byte clockChar[] = {
  B00000,
  B01110,
  B10101,
  B10111,
  B10001,
  B01110,
  B11011,
  B00000
};

#define ARROW_UP_CHAR byte(3)
byte arrowUpChar[] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000
};

#define ARROW_DOWN_CHAR byte(4)
byte arrowDownChar[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B00000
};

#define ARROW_RIGHT_CHAR byte(5)
byte arrowRightChar[] = {
  B00000,
  B00100,
  B00110,
  B11111,
  B11111,
  B00110,
  B00100,
  B00000
};

#define PRESS_BUTTON_CHAR byte(6)
byte pressButtonChar[] = {
  B11000,
  B11100,
  B01100,
  B00100,
  B00100,
  B00000,
  B01110,
  B11111
};

#define WALL_CHAR byte(7)
byte wallChar[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

// Cronómetros
gb::Clock ck;
gb::Clock p1ck, p2ck;
gb::Clock settings_ck;

// Tiempos
chess::Time gameTime, time1, time2;

//Turno actual (0 => ninguno, 1 => jugador 1, 2 => jugador 2)
byte turn;

// Pantalla actual
Screen currentScreen;

// Para la pantalla settings, representa si se están modificando los minutos o segundos (valor binario 0,1)
byte settings_timer_mode;

// Periodo de reloj
int gameTimerPeriod = 1000;

// Booleanos para la lectura de pulsadores y eventos
bool p1pressed = false;
bool p2pressed = false;
bool p1p2pressed = false;
bool p1Event = false;
bool p2Event = false;
bool p1p2Event = false;

// Booleanos para controlar el renderizado estático de la pantalla
bool welcomeOnce = false;
bool menuOnce = false;
bool settingsOnce = false;
bool clockOnce = false;

// Booleanos para control
bool paused = false;
bool blink = false;
bool finished = false;

// Renderizado estatico de la pantalla. Esta funcion renderiza por completo la pantalla indicada, sólo se debe usar al iniciarla.
void staticRender(Screen screen)
{
  if(screen == Screen::WELCOME)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write(TOWER_CHAR);
    lcd.print(" PROYECTO 24/25");
    lcd.setCursor(2, 1);
    lcd.print("GB & AM T31A");
    delay(3000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Pulse P1/P2   ");
    lcd.setCursor(0, 1);
    lcd.print("  PARA EMPEZAR  ");
  }

  if(screen == Screen::MENU)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write(PRESS_BUTTON_CHAR);
    lcd.print("P1 ");
    lcd.write(ARROW_RIGHT_CHAR);
    lcd.print(" ");
    lcd.write(CLOCK_CHAR);
    lcd.print(" RELOJ");
    lcd.setCursor(0, 1);
    lcd.write(PRESS_BUTTON_CHAR);
    lcd.print("P2 ");
    lcd.write(ARROW_RIGHT_CHAR);
    lcd.print(" ");
    lcd.write(SETTINGS_CHAR);
    lcd.print(" AJUSTES"); 
  }

  if(screen == Screen::SETTINGS)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write(CLOCK_CHAR);
    lcd.print(" " + gameTime.toString() + " ");
    lcd.write(ARROW_UP_CHAR);
    lcd.print("P1 ");
    lcd.write(ARROW_DOWN_CHAR);
    lcd.print("P2");
    lcd.setCursor(2, 1);
    lcd.write(PRESS_BUTTON_CHAR);
    lcd.print(" P1+P2 ");
    lcd.write(ARROW_RIGHT_CHAR);
    lcd.print(" OK");
  }

  if(screen == Screen::CLOCK)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("J1     ");
    lcd.write(WALL_CHAR);
    lcd.write(WALL_CHAR);
    lcd.print("     J2");
    lcd.setCursor(0, 1);
    lcd.print(time1.toString() + "  ");
    lcd.write(WALL_CHAR);
    lcd.write(WALL_CHAR);
    lcd.print("  " + time2.toString());
  }
}

// Renderizado dinamico de la pantalla. Esta funcion redibuja posiciones concretas de la pantalla. Se debe usar cada vez que haga
// falta actualizar datos. Además de la pantalla a renderizar, admite 2 parametros booleanos opcionales, estos son "parametros de
// conveniencia", es decir sirven para indicar informacion y/o estados especiales (por ejemplo en Screen::SETTINGS si flag1 es true
// se dibujaran los minutos con un parpadeo y si flag2 es true, entonces se dibujaran los segundos con dicho parpadeo).
void dynamicRender(Screen screen, bool flag1 = true, bool flag2 = true)
{
  if(screen == Screen::MENU)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write(TOWER_CHAR);
    lcd.print(": P1");
    lcd.setCursor(0, 1);
    lcd.write(SETTINGS_CHAR);
    lcd.print(": P2");
  }

  if(screen == Screen::SETTINGS)
  {
    lcd.setCursor(2, 0);
    if(flag1) lcd.print((gameTime.getMinutes() > 9 ? "" : "0") + String(gameTime.getMinutes()));
    else lcd.print("  ");
    lcd.print(":");
    if(flag2) lcd.print((gameTime.getSeconds() > 9 ? "" : "0") + String(gameTime.getSeconds()));
    else lcd.print("  ");
  }

  if(screen == Screen::CLOCK)
  {
    if(!flag1)
    {
      lcd.setCursor(0, 1);
      lcd.print(time1.toString() + "  ");
      lcd.write(WALL_CHAR);
      lcd.write(WALL_CHAR);
      lcd.print("  " + time2.toString());
    }
    else
    {
      if(flag2)
      {
        lcd.clear();
      }
      else
      {
        lcd.setCursor(0, 0);
        lcd.print("J1     ");
        lcd.write(WALL_CHAR);
        lcd.write(WALL_CHAR);
        lcd.print("     J2");
        lcd.setCursor(0, 1);
        lcd.print(time1.toString() + "  ");
        lcd.write(WALL_CHAR);
        lcd.write(WALL_CHAR);
        lcd.print("  " + time2.toString());
      }
    }
  }
}

// Restablece los datos por defecto
void reset()
{
  welcomeOnce = false;
  menuOnce = false;
  settingsOnce = false;
  clockOnce = false;
  blink = false;
  finished = false;
  gameTimerPeriod = 1000;
}

#pragma region ARDUINO

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  lcd.createChar(0, settingsChar);
  lcd.createChar(1, TOWERChar);
  lcd.createChar(2, clockChar);
  lcd.createChar(3, arrowUpChar);
  lcd.createChar(4, arrowDownChar);
  lcd.createChar(5, arrowRightChar);
  lcd.createChar(6, pressButtonChar);
  lcd.createChar(7, wallChar);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  currentScreen = Screen::WELCOME;

  Serial.begin(9600);
}

void loop() 
{
  if(!digitalRead(P1) && !p1p2pressed) 
  {
    p1ck.start();
    p1pressed = true;
  }

  if(!digitalRead(P2) && !p1p2pressed) 
  {
    p2ck.start();
    p2pressed = true;
  }

  if(!digitalRead(P1) && !digitalRead(P2))
  {
    p1pressed = false;
    p2pressed = false;
    p1p2pressed = true;
    p1ck.stop();
    p2ck.stop();
  }

  if(digitalRead(P1) && digitalRead(P2) && p1p2pressed)
  {
    p1p2pressed = false;
    p1p2Event = true;
  }

  if(digitalRead(P1) && p1pressed && p1ck.check(25))
  {
    p1pressed = false;
    p1ck.stop();
    p1Event = true;
  }

  if(digitalRead(P2) && p2pressed && p2ck.check(25))
  {
    p2pressed = false;
    p2ck.stop();
    p2Event = true;
  }

  switch(currentScreen)
  {
    case Screen::WELCOME:

      if(!welcomeOnce)
      {
        welcomeOnce = true;
        staticRender(Screen::WELCOME);
      }

      if(p1Event)
      {
        p1Event = false;
        currentScreen = Screen::SETTINGS;
      }

      if(p2Event)
      {
        p2Event = false;
        currentScreen = Screen::SETTINGS;
      }

      if(p1p2Event)
      {
        p1p2Event = false;
        currentScreen = Screen::SETTINGS;
      }

      break;
    case Screen::MENU:

      if(!menuOnce)
      {
        menuOnce = true;
        staticRender(Screen::MENU);
      }

      if(p1Event)
      {
        p1Event = false;
        reset();
        currentScreen = Screen::CLOCK;
      }

      if(p2Event)
      {
        p2Event = false;
        reset();
        currentScreen = Screen::SETTINGS;
      }

      break;
    case Screen::SETTINGS:

      if(!settingsOnce)
      {
        settings_timer_mode = 0;
        settingsOnce = true;
        staticRender(Screen::SETTINGS);
        settings_ck.start();
      }

      if(p1Event)
      {
        p1Event = false;
        
        if(settings_timer_mode == 0) gameTime.add(1, 0);
        if(settings_timer_mode == 1) gameTime.add(0, 1);
      }

      if(p2Event)
      {
        p2Event = false;

        if(settings_timer_mode == 0) gameTime.sub(1, 0);
        if(settings_timer_mode == 1) gameTime.sub(0, 1);
      }

      if(p1p2Event)
      {
        p1p2Event = false;

        if(settings_timer_mode == 1 && gameTime.isZero()) return;

        settings_timer_mode++;

        if(settings_timer_mode == 2)
        {
          reset();
          currentScreen = Screen::CLOCK;
        }
      }

      if(settings_ck.check(500))
      {
        if(settings_timer_mode == 0) dynamicRender(Screen::SETTINGS, true, true);
        if(settings_timer_mode == 1) dynamicRender(Screen::SETTINGS, true, true);
      }

      if(settings_ck.check(1000))
      {
        if(settings_timer_mode == 0) dynamicRender(Screen::SETTINGS, false, true);
        if(settings_timer_mode == 1) dynamicRender(Screen::SETTINGS, true, false);
        settings_ck.restart();
      }

      break;
    case Screen::CLOCK:

      if(!clockOnce)
      {
        clockOnce = true;
        turn = 0;

        time1 = gameTime;
        time2 = gameTime;

        staticRender(Screen::CLOCK);
      }

      if(p1Event)
      {
        paused = false;
        p1Event = false;
        if(turn == 0) ck.start();
        turn = 1;
      }

      if(p2Event)
      {
        paused = false;
        p2Event = false;
        if(turn == 0) ck.start();
        turn = 2;
      }

      if(p1p2Event)
      {
        p1p2Event = false;

        if(finished)
        {
          reset();
          return;
        }

        turn = 0;
        time1 = gameTime;
        time2 = gameTime;

        if(!paused) paused = true;
        else
        {
          currentScreen = Screen::SETTINGS;
          return;
        }
      }

      if(ck.check(gameTimerPeriod))
      {
        if(turn == 1) time1.sub(0, 1);
        if(turn == 2) time2.sub(0, 1);

        dynamicRender(Screen::CLOCK, finished, blink);
        ck.restart();

        if(time1.isZero() || time2.isZero()) 
        {
          finished = true;
          blink = !blink;
          gameTimerPeriod = 500;
        }
      }

      break;
  }
}

#pragma endregion
