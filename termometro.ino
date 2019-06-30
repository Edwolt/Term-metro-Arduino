/*
 Autor:Fabio Dias / https://github.com/yFabio11
 Autor:Eduardo Rocha / https://github.com/Edwolt
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define sensor A0
#define GRAUS 0

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
 
int entrada;

void setup() 
{
  lcd.begin(16, 2);

  byte graus[8] = {
    B00110,  
    B01001,
    B01001,
    B00110,
    B00000,
    B00000,
    B00000,
    B00000
  };

  byte termometro[5][8] = {
    {
      B00100,  
      B01010,
      B01010,
      B01010,
      B01010,
      B11101,
      B11111,
      B01110
    },
    {
      B00100,  
      B01010,
      B01010,
      B01010,
      B01110,
      B11101,
      B11111,
      B01110
    },
    {
      B00100,  
      B01010,
      B01010,
      B01110,
      B01110,
      B11101,
      B11111,
      B01110
    },
    {
      B00100,  
      B01010,
      B01110,
      B01110,
      B01110,
      B11101,
      B11111,
      B01110
    },
    {
      B00100,  
      B01110,
      B01110,
      B01110,
      B01110,
      B11101,
      B11111,
      B01110
    }
  };

  
  lcd.createChar (GRAUS, graus); 
  for(int i=0;i<5;i++){
    lcd.createChar (i + 1, termometro[i]);
  }
}

void loop() {

  entrada = analogRead(sensor);

  float celsius = (3.3*entrada*100)/1024;
  float kelvin = celsius+273.15;
  float fahrenheit = celsius*1.8+32; 

  lcd.clear();
  lcd.home();
  lcd.print("Temp");
  lcd.print("(");
  int termometro = (celsius - 15) / 5 + 1;
  termometro = (termometro<1)?1:(termometro>5)?5:termometro;
  lcd.print(char(termometro));
  lcd.print("): ");
  lcd.print(celsius);
  lcd.print(char(GRAUS));
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print(kelvin);
  lcd.print("K  ");
  lcd.print(fahrenheit);
  lcd.print(char(GRAUS));
  lcd.print("F");
  
  delay(1000);
}
