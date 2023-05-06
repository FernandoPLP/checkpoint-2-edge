#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32,16,2);
// Variaveis a serem adicionadas
int SensorUmidPino=2;
int ldrvariavel = 0;
int porcem=0;
int operacao; 


//Declarando entradas, lcd e sensores
void setup()
{
pinMode(A0, INPUT);
Serial.begin(9600);
pinMode(13, OUTPUT);//Vermelho
pinMode(12, OUTPUT);//Amarelo
pinMode(11, OUTPUT);//Verde
pinMode(10, OUTPUT);//som
pinMode(A1,INPUT);
lcd.begin(16,2);
lcd.init();
lcd.backlight();
Serial.begin(9600);


}

//Loop
void loop()
{
  //substituto do sensor de umidade
  int SensorUmidTensao=analogRead(SensorUmidPino);
  float porcem=map(SensorUmidTensao,0,1023,0,100);
  
  //manter a temperatura em °C
  int tmp = analogRead(A1);
  float voltage = (tmp * 5.0)/1024;
  float milliVolt = voltage * 1000;
  float tmpCel = (milliVolt-500)/10;
  
  //valores do lcd
  ldrvariavel = analogRead(A0);
  Serial.println(ldrvariavel);
  	 
 //Condições para os sensores
  operacao = Serial.parseInt();
 
 
 if(porcem > 50  ){// Umidade
  lcd.setCursor(0,0);
  lcd.print("Umidade OK");
  lcd.setCursor(0,1);
  lcd.print(porcem);
  delay(5000);
  lcd.clear();
  
 } 
  else if(porcem < 50 ){//Umidade
  lcd.setCursor(0,0);
  lcd.print("Umidade Baixa");
  lcd.setCursor(0,1);
  lcd.print(porcem);
  delay(5000);
  lcd.clear();
  
  
  } 
 
if ( 16 > tmpCel && tmpCel > 10 ) { //temperatura
    lcd.setCursor(0,1);
  	lcd.print("Agradavel");
    lcd.setCursor(0,0);
    lcd.print("Temperatura");
    delay(5000);
   	lcd.clear();
    
  }
else if (tmpCel > 16  ) { //temperatura
    lcd.setCursor(0,1);
  	lcd.print("Quente   ");
    lcd.setCursor(0,0);
    lcd.print("Temperatura");
   delay(5000);
    lcd.clear();
  }
else if (tmpCel < 10  ) { //temperatura
    lcd.setCursor(0,1);
  	lcd.print("Frio     ");
  	lcd.setCursor(0,0);
    lcd.print("Temperatura");
   delay(5000);
  	lcd.clear();
    
  } if (ldrvariavel > 1000 ) {//Luminosidade
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    delay(5000);
    lcd.clear();
  } else {
    if (ldrvariavel > 650  ) { //verde
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      lcd.setCursor(0,0);
      lcd.print("Estado da Luz:");
      lcd.setCursor(0,1);
      lcd.print("Estavel");
      delay(5000);
      lcd.clear();
      
    } else {
      if (ldrvariavel > 350  ) { //amar
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);
        lcd.setCursor(0,0);
        lcd.print("Estado da Luz     ");
        lcd.setCursor(0,1);
        lcd.print("Mediano");
        delay(5000);
        lcd.clear();
      } else {
        if (ldrvariavel > 150)  { // verm
          digitalWrite(11, LOW);
          digitalWrite(12, LOW);
          digitalWrite(13, HIGH);
  		  lcd.setCursor(0,0);
          lcd.print("Estado da Luz           ");
          lcd.setCursor(0,1);
          lcd.print("Instavel");
          delay(5000);
          lcd.clear();
          tone(10, 220, 5); 
  		 
        } 
      }
      }
    }
  

}