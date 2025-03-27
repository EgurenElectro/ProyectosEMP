//Autor: Gabriel Bravo Eguren - 2025
#include <LiquidCrystal_PCF8574.h>
#include <GBClock.h>

#define P1 27
#define P2 16
#define P3 17

LiquidCrystal_PCF8574 lcd(0x3F); 
gb::Clock clock1;
gb::Clock clock2;

bool p1Pressed = false;
bool p2Pressed = false;
bool p3Pressed = false;

int dashTime = 250;
unsigned long recordedTime = 0;

String morse[42][2] = {
  {"A", ".-"}, {"B", "-..."}, {"C", "-.-."}, {"D", "-.."},
  {"E", "."}, {"F", "..-."}, {"G", "--."}, {"H", "...."},
  {"I", ".."}, {"J", ".---"}, {"K", "-.-"}, {"L", ".-.."},
  {"M", "--"}, {"N", "-."}, {"O", "---"}, {"P", ".--."},
  {"Q", "--.-"}, {"R", ".-."}, {"S", "..."}, {"T", "-"},
  {"U", "..-"}, {"V", "...-"}, {"W", ".--"}, {"X", "-..-"},
  {"Y", "-.--"}, {"Z", "--.."}, {"0", "-----"}, {"1", ".----"}, 
  {"2", "..---"}, {"3", "...--"}, {"4", "....-"}, {"5", "....."}, 
  {"6", "-...."}, {"7", "--..."}, {"8", "---.."}, {"9", "----."},
  {".", ".-.-.-"}, {"?", "..--.."}, {",", "--..--"}, {"/", "-..-."},
  {"!", "-.-.--"}, {"=", "-...-"}
};

String morseChar;
String morseWord;

void render()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(morseWord);
  lcd.setCursor(0, 1);
  if(morseChar.length() < 15) lcd.print(">" + morseChar);
  else lcd.print("F" + morseChar);
}

void setup() 
{
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);

  render();
}

void loop() 
{
  if(!digitalRead(P1))
  {
    if(!clock1.started()) clock1.start();
    p1Pressed = true;
  }

  if(!digitalRead(P2)) 
  {
    if(!clock2.started()) clock2.start();
    p2Pressed = true;
  }

  if(!digitalRead(P3)) p3Pressed = true;
  
  //Escribir una señal
  if(digitalRead(P1) && p1Pressed)
  {
    p1Pressed = false;  
    recordedTime = clock1.stop();

    //Rebotes del pulsador, no cuentan
    if(recordedTime < 25) return;
    if(morseChar.length() == 15) return;

    if(recordedTime < dashTime) morseChar += "."; 
    else morseChar += "-";

    render();
  }

  //Borrar un caracter / borrar palabra si se presiona por 1 seg o mas
  if(digitalRead(P2) && p2Pressed)
  {
    p2Pressed = false;

    if(clock2.stop() >= 1000)
    {
      morseChar = "";
      morseWord = "";
    }
    else if(morseChar.length() > 0) 
    {
      morseChar = morseChar.substring(0, morseChar.length() - 1);
    }

    render();
  }

  //Confirmar caracter
  if(digitalRead(P3) && p3Pressed)
  {
    p3Pressed = false;
    bool found = false;

    for(int i = 0; i < 42; i++)
    {
      if(morse[i][1] == morseChar)
      {
        if(morseWord.length() < 16) morseWord += morse[i][0];
        found = true;
        break;
      }
    }

    if(!found)
    {
      lcd.clear();
      lcd.home();
      lcd.print("CARACTER NO");
      lcd.setCursor(0, 1);
      lcd.print("REGISTRADO");
      delay(2000);
    }

    morseChar = "";
    render();
  }
}
