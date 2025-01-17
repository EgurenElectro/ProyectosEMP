//------------------------------------------------------------
// Programa: A05_blink_pwm.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: Realiza un programa que, de forma indefinida, haga que un LED esté al 90%
//              de intensidad y cambie al 10% de intensidad (Como un parpadeo pero sin llegar nunca a apagarse
//              del todo ni a encenderse del todo)
//------------------------------------------------------------

#define D3 5

void setup() 
{
  pinMode(D3, OUTPUT); 
}

void loop() 
{
  analogWrite(D3, int(255.0 * 0.9));
  delay(100);
  analogWrite(D3, int(255.0 * 0.1));
  delay(100);
}
