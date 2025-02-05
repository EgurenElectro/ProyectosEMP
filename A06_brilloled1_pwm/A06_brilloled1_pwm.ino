//------------------------------------------------------------
// Programa: A06_brilloled1_pwm.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: Realiza un programa para controlar el nivel de brillo del led Verde de la
//              placa con un pulsador. Inicialmente brillo=0% y cada vez que pulse P1 el brillo se debe incrementar
//              en un 10% hasta llegar al 100%. Una nueva pulsación pondrá el brillo al 0% y comenzará de nuevo.
//------------------------------------------------------------

#define DG 18
#define P1 27

float intensidad;

void setup() 
{
  pinMode(P1, INPUT_PULLUP);
  pinMode(DG, OUTPUT);

  intensidad = 0;
}

void loop() 
{
  if(!digitalRead(P1))
  {
    intensidad += 255 * 0.1;

    if(intensidad == 255) intensidad = 0;
  }

  delay(200);

  analogWrite(DG, intensidad);
}
