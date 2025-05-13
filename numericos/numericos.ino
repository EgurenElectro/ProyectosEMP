
void setup() 
{
  Serial.begin(9600);
}

String toString(int num)
{
  int u = num % 10;
  int d = num % 100 - u;
  int c = num - d - u; 

  String str = "";

  if(c != 0)
  {
    if(c == 100) str += d == 0 && u == 0 ? "cien" : "ciento";
    if(c == 200) str += "doscientos";
    if(c == 300) str += "trescientos";
    if(c == 400) str += "cuatrocientos";
    if(c == 500) str += "quinientos";
    if(c == 600) str += "seiscientos";
    if(c == 700) str += "sietecientos";
    if(c == 800) str += "ochocientos";
    if(c == 900) str += "novecientos";

    if(d != 0 || u != 0) str += " ";
  }

  if(d != 0)
  {
    if(d == 10)
    {
      if(u == 1) str += "once";
      if(u == 2) str += "doce";
      if(u == 3) str += "trece";
      if(u == 4) str += "catorce";
      if(u == 5) str += "quince";
      return str;
    }

    if(d == 20) str += "veinte";
    if(d == 30) str += "treinta";
    if(d == 40) str += "cuarenta";
    if(d == 50) str += "cincuenta";
    if(d == 60) str += "sesenta";
    if(d == 70) str += "setenta";
    if(d == 80) str += "ochenta";
    if(d == 90) str += "noventa";

    if(u != 0) str += " y ";
  }

  if(u != 0)
  {
    if(u == 1) str += "uno";
    if(u == 2) str += "dos";
    if(u == 3) str += "tres";
    if(u == 4) str += "cuatro";
    if(u == 5) str += "cinco";
    if(u == 6) str += "seis";
    if(u == 7) str += "siete";
    if(u == 8) str += "ocho";
    if(u == 9) str += "nueve";
  }

  return str;
}

void loop()
{
  if(Serial.available())
  {
    int input = Serial.parseInt();

    Serial.println(toString(input));
  }
}
