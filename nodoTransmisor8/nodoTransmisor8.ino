/*El presente codigo envia datos desde un atmega8 acerca del sensado de algunos parámetros
*/

#define LED1 8
#define LED2 9
#define L1 A0
#define HS1 A1
#define HS2 A5
#define ONE_WI¿RE_BUS 10
#define LCD_BL 7

//#include <avr/wdt.h>
//#include <util/delay.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
//#include <DHT.h>
//#include <EEPROM.h>

// Data wire is plugged into port 10 on the Atmega8

OneWire oneWire(1);
//DallasTemperature temperatura1(&oneWire);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//#define DHTPIN 6
//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);

// Se definen las variables:
float temperaturaFloat = 0;
int temperaturaSuelo = 20;
int humedadSuelo1 = 0;
int humedadSuelo2 = 0;
int resistenciaSuelo1 = 0;
int resistenciaSuelo2 = 0;
int luminosidad = 0;
int luminosidadPorcentaje = 0;
float temperaturaAmbienteFloat;
float humedadAmbienteFloat;
int temperaturaAmbiente = 20;
int humedadAmbiente = 0;
int estado=1;

int contador=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LCD_BL,OUTPUT);
  digitalWrite(LCD_BL,HIGH);
  if(estado){
  digitalWrite(LED2,HIGH);
  }
  digitalWrite(LED1,LOW);
  Serial.begin(9600);
  //temperatura1.begin();
  //dht.begin();
  lcd.begin(16, 2);
}

void loop() {

// Se adquiere la temperatura y las lecturas analogas:
  //temperatura1.requestTemperatures();
  //temperaturaFloat=temperatura1.getTempCByIndex(0);
  temperaturaSuelo = 10*temperaturaFloat;
  luminosidad=analogRead(L1);
  luminosidadPorcentaje=luminosidad/10;
  if(luminosidadPorcentaje>100) luminosidadPorcentaje=100;
  humedadSuelo1=analogRead(HS1);
  resistenciaSuelo1=humedadSuelo1/5;
  if(humedadSuelo1>1000) resistenciaSuelo1=-1;
  /*if(humedadSuelo1>1000){
    resistenciaSuelo1=-1;
  }
  else{
    if(humedadSuelo1<0) humedadSuelo1=0;
    else{
      resistenciaSuelo1=(470*humedadSuelo1/(1023-humedadSuelo1)-11)*5;
    }
  }*/
  humedadSuelo2=analogRead(HS2);
  /*if(humedadSuelo2>1000){
    resistenciaSuelo2=-1;
  }
  else{
    if(humedadSuelo2<0) humedadSuelo2=0;
    else{
      resistenciaSuelo2=(470*humedadSuelo2/(1023-humedadSuelo1)-11)*5;
    }
  }*/
  resistenciaSuelo2=humedadSuelo2/5;
  if(humedadSuelo2>1000) resistenciaSuelo2=-1;
  temperaturaAmbienteFloat = 20;//dht.readTemperature();
  temperaturaAmbiente = 10*temperaturaAmbienteFloat;
  humedadAmbienteFloat = 27;//dht.readHumidity();
  humedadAmbiente = 10*humedadAmbienteFloat;

  // Se envia la trama por serial:
  Serial.write("*G");                //_E:
  //Serial.print(estado);
  //Serial.write(",");                //_L1:
  Serial.print(luminosidadPorcentaje);
  Serial.write(",");                //_TS1:
  Serial.print(temperaturaSuelo);
  Serial.write(",");                // _HS1:
  Serial.print(resistenciaSuelo1);
  Serial.write(",");                //_HS2:
  Serial.print(resistenciaSuelo2);
  Serial.write(",");                //_TA1:
  Serial.print(temperaturaAmbiente);
  Serial.write(",");                 //_TA2:
  Serial.print(humedadAmbiente);
  Serial.print("*");
  
// Desplegando información

  switch(contador%6){
    case 0:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TempSue:");
      lcd.setCursor(8, 0);
      lcd.print(temperaturaFloat);
      lcd.setCursor(15, 0);
      lcd.print("C");    
      lcd.setCursor(0, 1);
      lcd.print("TempAmb:");
      lcd.setCursor(8, 1);
      lcd.print(temperaturaAmbiente/10);
      lcd.setCursor(15, 1);
      lcd.print("C");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("R1:");
      lcd.setCursor(6, 0);
      lcd.print(10*resistenciaSuelo1);
      lcd.setCursor(13, 0);
      lcd.print("ohm");    
      lcd.setCursor(0, 1);
      lcd.print("R2:");
      lcd.setCursor(6, 1);
      lcd.print(10*resistenciaSuelo2);
      lcd.setCursor(13, 1);
      lcd.print("ohm");
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lumin:");
      lcd.setCursor(8, 0);
      lcd.print(luminosidadPorcentaje);
      lcd.setCursor(15, 0);
      lcd.print("%");    
      lcd.setCursor(0, 1);
      lcd.print("HumAtm");
      lcd.setCursor(8, 1);
      lcd.print(humedadAmbiente/10);
      lcd.setCursor(15, 1);
      lcd.print("%");
      break;
    default:
      break;
  }
  digitalWrite(LED1,!digitalRead(LED1));
  contador++;
  delay(1000);
}
