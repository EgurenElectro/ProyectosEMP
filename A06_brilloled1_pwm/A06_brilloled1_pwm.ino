//------------------------------------------------------------
// Programa: A06_brilloled1_pwm.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (17-01-2025)
// Descripción: Realiza un programa para controlar el nivel de brillo del led Verde de la
//              placa con un pulsador. Inicialmente brillo=0% y cada vez que pulse P1 el brillo se debe incrementar
//              en un 10% hasta llegar al 100%. Una nueva pulsación pondrá el brillo al 0% y comenzará de nuevo
//------------------------------------------------------------

#define GL 18
#define P1 27

int brightness = 0;

void setup() 
{
  pinMode(GL, OUTPUT);
  pinMode(P1, INPUT_PULLUP);
}

void loop() 
{
  if(!digitalRead(P1))
  {
    if(brightness < 255) brightness += int(255 * 0.1);
    else brightness = 0;
  } 

  analogWrite(GL, brightness);

  delay(400);
}
