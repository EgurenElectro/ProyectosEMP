//------------------------------------------------------------
// Programa: A09_brilloled4_ldr.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (13-01-2025)
// Descripción: Realiza un programa para controlar el brillo de los cuatro leds de la placa en
//              función inversa de la luz que reciba la LDR. En ausencia de luz todos los leds estarán al 100% y con
//              máxima iluminación al 0%.
//------------------------------------------------------------

#define D1 12
#define D2 13
#define D3 5
#define D4 23

#define LDR 2

int ldr = 0;

void setup() 
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  Serial.begin(9600);
}

void loop() 
{
  ldr = map(analogRead(LDR), 0, 4095, 0, 255);

  Serial.println(ldr);

  analogWrite(D1, 255 - ldr);
  analogWrite(D2, 255 - ldr); 
  analogWrite(D3, 255 - ldr);
  analogWrite(D4, 255 - ldr);

}
