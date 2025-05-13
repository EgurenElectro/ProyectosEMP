void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  if(Serial.available())
  {
    int input = Serial.parseInt();

    String lista = "";

    for(int i = 1; i <= input; i++)
    {
      if(input % i == 0) lista += String(i) + ", ";
    }

    lista = lista.substring(0, lista.length() - 2);

    Serial.println("Divisores de " + String(input) + ": " + lista);
  }
}
