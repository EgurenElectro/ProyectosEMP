#include <LiquidCrystal_PCF8574.h>

#define P1 27
#define P2 16
#define WT 250

LiquidCrystal_PCF8574 lcd(0x3F); 

bool p1down = false;
bool p2down = false;

String estaciones[5] = {
  "GUADALAJARA",
  "AZUQUECA",
  "MECO",
  "ALCALA UNIVERSIDAD",
  "ALCALA DE HENARES"
};

int direccion = 0;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);

  menu();
}

void menu()
{
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("P1->Start");
  lcd.setCursor(3, 1);
  if(direccion == 0) lcd.print("IDA");
  else lcd.print("VUELTA");
}

void loop() 
{
  if(!digitalRead(P1)) p1down = true;
  if(!digitalRead(P2)) p2down = true;

  if(digitalRead(P2) && p2down)
  {
    direccion = direccion == 0 ? 1 : 0;
    p2down = false;
    menu();
  }

  if(digitalRead(P1) && p1down)
  {
    p1down = false;

    String texto = "Proximas estaciones: ";

    for(int i = (direccion == 0 ? 0 : 4); (direccion == 0 ? (i < 5) : (i >= 0)); (direccion == 0 ? i++ : i--))
    {
      texto += estaciones[i];
      if(direccion == 0 && i != 4) texto += ", ";
      if(direccion == 1 && i != 0) texto += ", "; 
    }
    
    lcd.setCursor(0,0);

    for(int i = 0; i < 16; i++)
    {
      texto = " " + texto;
    }

    while(texto.length() > 0)
    {
      lcd.clear();
      texto = texto.substring(1);
      lcd.print(texto.substring(0, 16));
      delay(WT);
    }

    delay(800);
    menu();
  }
}
