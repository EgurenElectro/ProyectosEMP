//------------------------------------------------------------
// Programa: LCD08_especial_bat.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A 
// Descripción: Realizar un programa que cree seis caracteres especiales que muestren
//              una pila al 0%, 20%, 40%, 60%, 80% y 100%. Inicialmente se muestra el símbolo de 00% y cada vez
//              que se pulse P1 se debe incrementar la carga en un 20% y mostrar el símbolo correcto. Si se deja
//              pulsado P1 se incrementa la carga cada 500ms
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define P1 27

LiquidCrystal_PCF8574 lcd(0x3F); 

bool update = true;
int carga = 0;

byte bat[6][8] = {
  {
    B01100,
    B10010,
    B10010,
    B10010,
    B10010,
    B10010,
    B10010,
    B11110
  }, {
    B01100,
    B10010,
    B10010,
    B10010,
    B10010,
    B10010,
    B11110,
    B11110
  }, {
    B01100,
    B10010,
    B10010,
    B10010,
    B10010,
    B11110,
    B11110,
    B11110
  }, {
    B01100,
    B10010,
    B10010,
    B10010,
    B11110,
    B11110,
    B11110,
    B11110
  }, {
    B01100,
    B10010,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110
  },{
    B01100,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110
  }
};

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(P1, INPUT_PULLUP);
}

void loop() 
{
  if(!digitalRead(P1))
  {
    if(carga < 5)
    {
      carga++;
      update = true;
      delay(500);
    }
  }

  if(update)
  {
    lcd.clear();

    lcd.createChar(0, bat[carga]); 
    lcd.clear(); 
    lcd.write((byte)0); 

    if(carga == 0) lcd.print(" 00%");
    if(carga == 1) lcd.print(" 20%");
    if(carga == 2) lcd.print(" 40%");
    if(carga == 3) lcd.print(" 60%");
    if(carga == 4) lcd.print(" 80%");
    if(carga == 5) lcd.print(" 100%");
    
    update = false;
  }
} 
