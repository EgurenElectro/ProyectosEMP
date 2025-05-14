#include <LiquidCrystal_PCF8574.h>
#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 8
#define PIN 26

#define BUZZER 14

#define POT 34

#define P1 27
#define P2 16
#define P3 17

#define D1 12
#define D2 13
#define D3 5
#define D4 23

LiquidCrystal_PCF8574 lcd(0x3F); 
Adafruit_NeoPixel tira = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define EURO byte(0)
byte euroChar[] = {
  B00110,
  B01000,
  B01000,
  B00110,
  B00110,
  B01000,
  B01000,
  B00110
};


String tipoGas[4] = {"Gas.95", "Gas.98", "D.e+", "D.Nexa"};
float pvpGas[4] = {1.31, 1.47, 1.32, 1.43};

String pantalla = "inicio";
int gasSeleccionado = 0;

long tempSurtidorP1 = -1;
long tempSurtidorP2 = -1;

long tempAlarma = -1;
bool alarmaActiva = false;
int contAlarma = 0;

long tempAlarma2 = -1;
bool alarma2Activa = false;
int contAlarma2 = 0;

float dineroCliente = 0;

bool p1presionado = false;
bool p2presionado = false;
bool p3presionado = false;

bool dibujarInicio = true;
bool dibujarSurtidor = false;
bool dibujarSurtidor2 = false;

void alarma()
{
  if(contAlarma == 2) 
  {
    contAlarma = 0;
    alarmaActiva = false;
  }

  if(!alarmaActiva) return;

  if(tempAlarma == -1) tempAlarma = millis();

  if(millis() - tempAlarma >= 150)
  {
    tone(BUZZER, 1024, 50);
    contAlarma++;
    tempAlarma = millis();
  }
}

void alarma2()
{
  if(contAlarma2 == 3) 
  {
    contAlarma2 = 0;
    alarma2Activa = false;
  }

  if(!alarma2Activa) return;

  if(tempAlarma2 == -1) tempAlarma2 = millis();

  if(millis() - tempAlarma2 >= 150)
  {
    tone(BUZZER, 1024, 50);
    contAlarma2++;
    tempAlarma2 = millis();
  }
}

void setup() 
{
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  lcd.createChar(0, euroChar);

  Serial.begin(9600);
  Serial.println("Surtidor listo. Introduzca nuevo precio en centimos (0-500)");

  tira.begin();
  tira.setBrightness(64);
  tira.clear();

  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  lcd.clear();
  lcd.home();
  lcd.print("Simulador de");
  lcd.setCursor(0, 1);
  lcd.print("combustible v1.0");
  delay(2000);
}

void loop() 
{
  if(!digitalRead(P1)) p1presionado = true;
  if(!digitalRead(P2)) p2presionado = true;
  if(!digitalRead(P3)) p3presionado = true;

  if(pantalla == "inicio")
  {
    if(dibujarInicio)
    {
      dibujarInicio = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("By: G.Bravo");
      lcd.setCursor(0, 1);
      lcd.print("   P1-> Start");
    }

    if(digitalRead(P1) && p1presionado)
    {
      p1presionado = false;
      pantalla = "surtidor";
      dibujarSurtidor = true;
    }
  }

  if(pantalla == "surtidor")
  {
    if(dibujarSurtidor)
    {
      dibujarSurtidor = false;

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(tipoGas[gasSeleccionado]);
      int espacios = 16 - (tipoGas[gasSeleccionado].length() + String(pvpGas[gasSeleccionado]).length() + 1);
      
      for(int i = 0; i < espacios; i++) lcd.print(" ");

      lcd.print(String(pvpGas[gasSeleccionado]));
      lcd.write(EURO);

      lcd.setCursor(0, 1);
      lcd.print("EUROS:" + String(dineroCliente));
      lcd.write(EURO);
    }

    int valorPot = map(analogRead(POT), 0, 4095, 0, 3);
    
    if(valorPot != gasSeleccionado)
    {
      gasSeleccionado = valorPot;
      dibujarSurtidor = true;
    }

    digitalWrite(D1, gasSeleccionado == 0);
    digitalWrite(D2, gasSeleccionado == 1);
    digitalWrite(D3, gasSeleccionado == 2);
    digitalWrite(D4, gasSeleccionado == 3);

    int r, g, b;

    if(gasSeleccionado == 0)
    {
      r = 0;
      g = 50;
      b = 0;
    }

    if(gasSeleccionado == 1)
    {
      r = 50;
      g = 0;
      b = 0;
    }

    if(gasSeleccionado == 2)
    {
      r = 50;
      g = 50; 
      b = 0;
    }

    for(int i = 0; i < NUMPIXELS; i++)
    {
      tira.setPixelColor(i, tira.Color(r, g, b));
      tira.show();
    }

    if(!digitalRead(P1))
    {
      if(tempSurtidorP1 == -1) tempSurtidorP1 = millis();

      if(millis() - tempSurtidorP1 >= 200) 
      {
        dineroCliente += 0.5;
        dibujarSurtidor = true;
        tempSurtidorP1 = millis();
      }
    }

    if(!digitalRead(P2) && dineroCliente > 0.0)
    {
      if(tempSurtidorP2 == -1) tempSurtidorP2 = millis();

      if(millis() - tempSurtidorP2 >= 200) 
      {
        dineroCliente -= 0.5;
        dibujarSurtidor = true;
        tempSurtidorP2 = millis();
      }
    }

    if(Serial.available())
    {
      int input = Serial.parseInt();

      if(input >= 0 && input <= 500)
      {
        int euros = input / 100;
        float cent = (input % 100) * 0.01;

        float precio = euros + cent;

        pvpGas[gasSeleccionado] = precio;
        dibujarSurtidor = true;
      }
      else
      {
        alarmaActiva = true;
      }
    }

    if(digitalRead(P3) && p3presionado)
    {
      p3presionado = false;
      pantalla = "surtidor2";
      dibujarSurtidor2 = true;
    }
  }

  if(pantalla == "surtidor2")
  {
    if(dibujarSurtidor2)
    {
      dibujarSurtidor2 = false;
      lcd.clear();
      lcd.print(tipoGas[gasSeleccionado]);
      int espacios = 16 - (tipoGas[gasSeleccionado].length() + String("P3>Reset").length());
      
      for(int i = 0; i < espacios; i++) lcd.print(" ");

      lcd.print("P3>Reset");
      lcd.setCursor(0, 1);
      lcd.print(String(dineroCliente));
      lcd.write(EURO);

      String textoInferior = dineroCliente == 0.0 ? "<FIN>" : "P1>REPOS";

      espacios = 16 - (String(dineroCliente).length() + 1 + textoInferior.length());

      for(int i = 0; i < espacios; i++) lcd.print(" ");

      lcd.print(textoInferior);
    }

    if(digitalRead(P3) && p3presionado)
    {
      p3presionado = false;
      pantalla = "surtidor";
      dibujarSurtidor = true;
      tempSurtidorP1 = -1;
    }

    if(!digitalRead(P1))
    {
      if(dineroCliente > 0)
      {
        if(tempSurtidorP1 == -1) tempSurtidorP1 = millis();

        if(millis() - tempSurtidorP1 >= 100)
        {
          tempSurtidorP1 = millis();
          dineroCliente -= 0.5;
          dibujarSurtidor2 = true;
        }
      }
      else
      {
        if(!alarma2Activa)
        {
          alarma2Activa = true;
        }
      }
    }
  }

  alarma();
  alarma2();
}
