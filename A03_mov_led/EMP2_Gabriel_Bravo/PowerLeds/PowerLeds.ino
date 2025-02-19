//------------------------------------------------------------
// Programa: PowerLeds.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A 
// Descripción: Controla el brillo de dos LEDS independientemente con un potenciómetro.
//------------------------------------------------------------

#include <LiquidCrystal_PCF8574.h>

#define D1 12
#define D4 23
#define DV 18
#define DR 19

#define POT 34
#define P1 27

LiquidCrystal_PCF8574 lcd(0x3F); 

//Si opcion = 0, entonces actuará sobre el LED D1, si por el contrario es 1, actuará sobre el LED D4.
byte opcion = 0;

int porcentajeD1 = 0;
int brilloD1 = 0;

int porcentajeD4 = 0;
int brilloD4 = 0;

//Variable para controlar el evento del pulsador P1 y que se ejecute en flanco de subida.
bool p1down = false;

//Variable para controlar el "frame" en el que se debe encender DR o no.
bool brillarDR = true;

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  pinMode(P1, INPUT_PULLUP);

  pinMode(DV, OUTPUT);
  pinMode(DR, OUTPUT);

  lcd.home();
  lcd.print("Gabriel Bravo E.");
  delay(2000);
}

void loop() 
{
  if(!digitalRead(P1)) p1down = true;

  int valorPWD = map(analogRead(POT), 0, 4095, 0, 255);
  int valorPorcentual = map(analogRead(POT), 0, 4095, 0, 100);

  //Se activa justo despues de dejar de presionar P1
  if(digitalRead(P1) && p1down)
  {
    if(opcion == 0) opcion = 1;
    else opcion = 0;

    p1down = false;
  }

  lcd.clear();

  if(opcion == 0)
  {
    porcentajeD1 = valorPorcentual;
    brilloD1 = valorPWD;

    lcd.setCursor(0,0);
    lcd.printf("(X)BrilloD1:%d%", porcentajeD1);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.printf("( )BrilloD4:%d%", porcentajeD4);
    lcd.print("%");
  }
  else
  {
    porcentajeD4 = valorPorcentual;
    brilloD4 = valorPWD;

    lcd.setCursor(0,0);
    lcd.printf("( )BrilloD1:%d", porcentajeD1);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.printf("(X)BrilloD4:%d", porcentajeD4);
    lcd.print("%");
  }

  analogWrite(D1, brilloD1);
  analogWrite(D4, brilloD4);

  if(porcentajeD1 == 100 || porcentajeD4 == 100)
  {
    if(brillarDR) digitalWrite(DR, 1);
    else digitalWrite(DR, 0);

    digitalWrite(DV, 0);

    brillarDR = !brillarDR;
  }
  else
  {
    digitalWrite(DR, 0);
    digitalWrite(DV, 1);
  }

  delay(100);
}
