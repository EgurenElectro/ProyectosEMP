//------------------------------------------------------------
// Programa: LCD05_canalesTV.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A 
// Descripción: El programa debe mostrar en la primera
//              línea del lcd el texto “Vol: MUTE” y en la segunda “Canal: TVE1”.
//              El potenciómetro controlará el volumen mostrando en la
//              primera línea del lcd (posiciones 4 a 15) un número de asteriscos proporcional al valor leído del
//              potenciómetro. Máximo 11 y mínimo 1. Si el volumen es
//              P1 Cambiará el nombre de la cadena en la segunda línea de forma secuencial. Las emisoras son:
//              TVE1, TVE2, Antena 3, Cuatro y Telecinco. Si se vuelve a pulsar P1 se reinicia la lista
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define P1 27

#define POT 34

LiquidCrystal_PCF8574 lcd(0x3F); 

bool update = true;

bool p1down = false;
int cursor = 0;
int volumen;

char* canales[5] = {
  "TVE1",
  "TVE2",
  "Antena 3",
  "Cuatro",
  "Telecinco"
};

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(P1, INPUT_PULLUP);
}

void loop() 
{
  int pot = map(analogRead(POT), 0, 4095, 0, 11);

  if(!digitalRead(P1)) p1down = true;

  if(digitalRead(P1) && p1down)
  {
    cursor = cursor == 4 ? cursor = 0 : cursor + 1;
    update = true;
    p1down = false;
  }

  if(pot != volumen)
  {
    volumen = pot;
    update = true;
  }

  if(update)
  {
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Vol: ");

    if(volumen == 0) lcd.print("MUTE");
    else
    {
      for(int i = 0; i < volumen; i++) lcd.print("*");
    }

    lcd.setCursor(0,1);
    lcd.print("Canal: ");
    lcd.print(canales[cursor]);

    update = false;
  }
} 
