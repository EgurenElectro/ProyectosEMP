#define P1 27

/*
  Configuración LEDs:

  L0    L4
  L1 L3 L5
  L2    L6

  [L0, L1, L2, L3, L4, L5, L6]
*/

struct Dice
{
  byte num;
  byte leds[7] = {0, 0, 0, 0, 0, 0, 0};
};


Dice generate()
{
  auto num = random(1, 7);

  Dice dice;
  dice.num = num;

  switch(num)
  {
  case 1: dice.leds[3] = 1; break;
  case 2: dice.leds[0] = 1; dice.leds[6] = 1; break;
  case 3: dice.leds[0] = 1; dice.leds[3] = 1; dice.leds[6] = 1; break;
  case 4: dice.leds[0] = 1; dice.leds[2] = 1; dice.leds[4] = 1; dice.leds[6] = 1; break;
  case 5: dice.leds[0] = 1; dice.leds[2] = 1; dice.leds[3] = 1; dice.leds[4] = 1; dice.leds[6] = 1; break;
  case 6: dice.leds[0] = 1; dice.leds[1] = 1; dice.leds[2] = 1; dice.leds[4] = 1; dice.leds[5] = 1; dice.leds[6] = 1; break;
  } 

  return dice;
}

bool p1Pressed = false;

void setup() 
{
  pinMode(P1, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() 
{
  if(!digitalRead(P1)) p1Pressed = true;

  if(digitalRead(P1) && p1Pressed)
  {
    p1Pressed = false;

    auto dice = generate();

    Serial.printf("Numero: %d\n", dice.num);
    for(int i = 0; i < 7; i++)
    {
      Serial.printf("L%d:", i);
      String status = dice.leds[i] == 1 ? "ON" : "OFF";
      Serial.println(status);
    }

    Serial.println("--------------\n");
  }

}
