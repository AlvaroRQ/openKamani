/*El presente codigo envia datos desde un atmega8 acerca del sensado de algunos parámetros
*/

#define LED1 8
#define LED2 9
#define L1 A0
#define HS1 A1
#define HS2 A5
#define ONE_WIRE_BUS 10

//#include <avr/wdt.h>
//#include <util/delay.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
//*#include <DHT.h>
//#include <EEPROM.h>

// Data wire is plugged into port 10 on the Atmega8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temperatura1(&oneWire);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//#define DHTPIN 6
//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);

// Se definen las variables:
float temperaturaFloat = 0;
int temperaturaSuelo = 0;
int humedadSuelo1 = 0;
int humedadSuelo2 = 0;
int luminosidad = 0;
int temperaturaAmbiente = 20;
int humedadAmbiente = 0;
int estado=1;

int contador=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  if(estado){
  digitalWrite(LED2,HIGH);
  }
  digitalWrite(LED1,LOW);
  Serial.begin(9600);
  temperatura1.begin();
  //dht.begin();
  lcd.begin(16, 2);
}

void loop() {
  //float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  //float t = dht.readTemperature();
  
// Se adquiere la temperatura y las lecturas analogas:
  temperatura1.requestTemperatures();
  temperaturaFloat=temperatura1.getTempCByIndex(0);
  temperaturaSuelo = 100*temperaturaFloat;
  luminosidad=analogRead(L1);
  humedadSuelo1=analogRead(HS1);
  humedadSuelo2=analogRead(HS2);
  //temperaturaAmbiente;
  //humedadAmbiente;

  // Se envia la trama por serial:
  Serial.write("_E:");
  Serial.print(estado);
  Serial.write("_L1:");
  Serial.print(luminosidad);
  Serial.write("_TS1:");
  Serial.print(temperaturaSuelo);
  Serial.write("_HS1:");
  Serial.print(humedadSuelo1);
  Serial.write("_HS2:");
  Serial.print(humedadSuelo2);
  Serial.write("_TA1:");
  Serial.print(temperaturaAmbiente);
  Serial.write("_TA2:");
  Serial.print(humedadAmbiente);
  Serial.print("\n");
  
// Desplegando información
/*
  switch(contador%3){
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("TempSue:");
      lcd.setCursor(8, 0);
      lcd.print(temperaturaFloat);
      lcd.setCursor(14, 0);
      lcd.print("°C");    
      lcd.setCursor(0, 1);
      lcd.print("TempAmb:");
      lcd.setCursor(8, 1);
      lcd.print(temperaturaAmbiente);
      lcd.setCursor(14, 1);
      lcd.print("°C");
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Hume1:");
      lcd.setCursor(8, 0);
      lcd.print(humedadSuelo1);
      lcd.setCursor(14, 0);
      lcd.print("cB");    
      lcd.setCursor(0, 1);
      lcd.print("Hume2:");
      lcd.setCursor(8, 1);
      lcd.print(humedadSuelo2);
      lcd.setCursor(14, 1);
      lcd.print("cB");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Lumin:");
      lcd.setCursor(8, 0);
      lcd.print(luminosidad);
      lcd.setCursor(14, 0);
      lcd.print("°C");    
      lcd.setCursor(0, 1);
      lcd.print("HumAtm");
      lcd.setCursor(8, 1);
      lcd.print(humedadAmbiente);
      lcd.setCursor(15, 1);
      lcd.print("%");
      break;
  }*/
  digitalWrite(LED1,!digitalRead(LED1));
  contador++;
  delay(2000);
}
