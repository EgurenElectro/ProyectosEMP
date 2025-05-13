
char abecedario[26] = {
  'a', 'b', 'c', 
  'd', 'e', 'f', 
  'g', 'h', 'i', 
  'j', 'k', 'l', 
  'm', 'n', 'o', 
  'p', 'q', 'r', 
  's', 't', 'u', 
  'v', 'w', 'x', 
  'y', 'z'
};

int numAbecedario(char c)
{
  for(int i = 0; i < 26; i++)
  {
    if(abecedario[i] == c) return i;
  }

  return -1;
}

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available())
  {
    String input = Serial.readString();
    input.toLowerCase();


    for(int i = 0; i < input.length(); i++)
    {
      if(input[i] = ' ') continue;
      else if(input[i] == 'z') input[i] = 'a';
      else input[i] = abecedario[numAbecedario(input[i]) + 1];
    }

    input.toUpperCase();

    Serial.println(input);
  }
}
