#include <LiquidCrystal_PCF8574.h>

#define P1 27
#define WT 250

LiquidCrystal_PCF8574 lcd(0x3F); 

bool p1down = false;
int pos = 0;

byte tren[2][8] = {
  { //Locomotora
    B00000,
    B00011,
    B00100,
    B00000,
    B01110,
    B10110,
    B11110,
    B11110
  }, { //Vagon
    B00000,
    B00000,
    B00000,
    B00000,
    B11110,
    B10010,
    B11110,
    B11110
  }
};

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  
  pinMode(P1, INPUT_PULLUP);
  
  lcd.createChar(0, tren[0]);
  lcd.createChar(1, tren[1]);

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("P1->Start");
}

void loop() 
{
  if(!digitalRead(P1)) p1down = true;

  if(digitalRead(P1) && p1down)
  {
    p1down = false;

    String texto = "Proximas estaciones: AZUQUECA, MECO, ALCALA UNIVERSIDAD, ALCALA DE HENARES";

    for(int i = 15; i >= 0; i--)
    {
      lcd.clear();

      //#region Animacion
      lcd.setCursor(i, 1);
      lcd.write(0); 

      for(int j = i + 1; j < 16; j++)
      {
        lcd.setCursor(j, 1);
        lcd.write(1); 
      }
      //#endregion

      lcd.setCursor(i, 0);
      lcd.print(texto.substring(0, 16 - i));
      delay(WT);
    }

    int contAnimacion = 15;

    while(texto.length() > 0)
    {
      lcd.clear();

      //#region Animacion
      for(int j = 0; j < contAnimacion; j++)
      {
        lcd.setCursor(j, 1);
        lcd.write(1);
      }

      contAnimacion--;
      //#endregion

      lcd.setCursor(0,0);
      texto = texto.substring(1);
      lcd.print(texto.substring(0, 16));
      delay(WT);
    }

    delay(800);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("P1->Start");
  }
}
