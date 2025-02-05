#define BUZ 14
#define POT 34

#define P1 27

int vpot;

byte tabla[10][4] = {
  {0, 0, 0, 0},
  {0, 0, 0, 1},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 1, 0, 0},
  {0, 1, 0, 1},
  {0, 1, 1, 0},
  {0, 1, 1, 1},
  {1, 0, 0, 0},
  {1, 0, 0, 1},
};

void setup() 
{
  Serial.begin(9600);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(P1, INPUT_PULLUP);
}

void loop() 
{
  vpot = analogRead(POT);

  int m = vpot / 1000;
  int c = (vpot - (m*1000)) / 100;
  int d = (vpot - ((m*1000) + (c*100))) / 10;
  int u = vpot - ((m*1000) + (c*100) + (d*10));

  if(!digitalRead(P1))
  {
    Serial.println("-----------------\n");
    Serial.printf("ValorPot: %d\nUnidades: %d\n", vpot, u);

    if(vpot % 2 == 0) Serial.println("Valor par: Si");
    else Serial.println("Valor par: No\n");
  }

  digitalWrite(D1, tabla[u][0]);
  digitalWrite(D2, tabla[u][1]);
  digitalWrite(D3, tabla[u][2]);
  digitalWrite(D4, tabla[u][3]);

  delay(100);
}
