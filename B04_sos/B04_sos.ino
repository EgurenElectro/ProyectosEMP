//------------------------------------------------------------
// Programa: B04_sos.ino (ESP32 + BIOS Shield)
// Autor: Gabriel Bravo Eguren T31A (15-01-2025)
// Descripción: Realizar un programa que genere una señal de S.O.S en código Morse cada vez que se
//              pulse alguno de los pulsadores P1, P2 o P3. Resolver el ejercicio usando un bucle while o for.
//              Nota:
//                En el código morse la señal de SOS consiste en 3 pitidos cortos, tres largos y tres cortos seguidos de
//                un tiempo de silencio. En nuestro ejemplo el pitido corto será de T=200ms, el largo de T=400ms, el
//                tiempo entre pitidos de 300ms y el tiempo de espera entre señales de SOS de 2 segundos.
//------------------------------------------------------------

#define P1 27
#define P2 16
#define P3 17

#define BUZZER 14

int frec = 1200;

bool p1down = false;
bool p2down = false;
bool p3down = false;

void setup() 
{
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(P3, INPUT_PULLUP);
}

void SOS()
{
  for(int i = 0; i < 3; i++)
  {
    tone(BUZZER, frec);
    delay(200);
    noTone(BUZZER);
    delay(300);
  }

  for(int i = 0; i < 3; i++)
  {
    tone(BUZZER, frec);
    delay(400);
    noTone(BUZZER);
    delay(300);
  }

  for(int i = 0; i < 3; i++)
  {
    tone(BUZZER, frec);
    delay(200);
    noTone(BUZZER);
    delay(300);
  }

  delay(2000);
}

void loop() 
{
  if(!digitalRead(P1)) p1down = true;
  if(!digitalRead(P2)) p2down = true;
  if(!digitalRead(P3)) p3down = true;

  if(digitalRead(P1) && p1down)
  {
    SOS();
    p1down = false;
  }
}
