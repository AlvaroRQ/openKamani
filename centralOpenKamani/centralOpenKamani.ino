// Arduino Mega
#include <avr/wdt.h>

#define SERIAL_CPU Serial
#define SERIAL_EMB Serial1
#define SERIAL_BTH Serial2
//#define SERIAL_SIM Serial3 /Ya definida en la libreria sim800basic

#include <sim800basic.h>

SIM800basic internet(3,9600,1);


int inByte;
int simByte;
unsigned long tiempo;
int contador=0;

char SENSOR[6][5]={};

int lugar=0;

int estado = 0;
// 0-> estado normal
// 1-> obteniendo L
// 2-> obteniendo TS

void setup() {
  // put your setup code here, to run once:
  SERIAL_CPU.begin(9600);
  SERIAL_EMB.begin(9600);
  SERIAL_BTH.begin(9600);
  //SERIAL_SIM.begin(9600);
  //SERIAL_SIM.write();
  
  // Se inicializa el modulo SIM900
  delay(3000);
  internet.mandarComandoATconRespuesta("AT+CIPSHUT");
  delay(10);
  internet.mandarComandoATconRespuesta("AT+CIPSTATUS");
  delay(10);
  internet.mandarComandoATconRespuesta("AT+CIPMUX=0");
  delay(10);
  internet.mandarComandoATconRespuesta("AT+SAPBR=3,1,\"APN\",\"internet.nuevatel.com\"");
  //internet.mandarComandoATconRespuesta("AT+SAPBR=3,1,\"APN\",\"internet.tigo.bo\"");
  delay(10);
  internet.mandarComandoATconRespuesta("AT+SAPBR=3,1,\"USER\",\"VIVAINTERNET\"");
  //internet.mandarComandoATconRespuesta("AT+SAPBR=3,1,\"USER\",\"TIGOINTERNET\"");
  delay(10);
  internet.mandarComandoATconRespuestaEspera("AT+SAPBR=1,1\r\n",20);
  delay(2000);
  //wdt_enable(WDTO_8S);
/*
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 250000;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
  */
  
  tiempo = millis();
}
/*
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  //digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
/*
  SERIAL_CPU.println(SENSOR[0]);
  SERIAL_CPU.println(SENSOR[1]);
  SERIAL_CPU.println(SENSOR[2]);
  SERIAL_CPU.println(SENSOR[3]);
  SERIAL_CPU.println(SENSOR[4]);
  SERIAL_CPU.println(SENSOR[5]);
  SERIAL_CPU.println("_");
  internet.mandarComandoATconRespuesta("AT+HTTPINIT\r\n");
  delay(10);
  internet.mandarCaracter("AT+HTTPPARA=\"URL\",\"http://kamani.solunes.com/api/reportar/cultivo-altiplano?presion=2&n1=1,");
  internet.mandarCaracter((String)contador);
  internet.mandarComandoATconRespuesta(",123,555,555,555,60&n2=1,321,555,555,555,555,555\"");
  delay(10);
  internet.mandarComandoATconRespuesta("AT+HTTPACTION=0\r\n");
  delay(4000);
  internet.mandarComandoATconRespuesta("AT+HTTPREAD\r\n");
  delay(2000);
  internet.mandarComandoATconRespuesta("AT+HTTPTERM\r\n");
  delay(10);
  while(millis()-tiempo<1000){true;}
  
  SERIAL_CPU.print("Datos subidos a la nube ;-)\n");
  tiempo = millis();
  contador++;
}*/

void loop(){
  //wdt_reset();
  // put your main code here, to run repeatedly:
  if (SERIAL_EMB.available()) {
    inByte = SERIAL_EMB.read();
    SERIAL_BTH.write(inByte);
    SERIAL_CPU.write(inByte);

    // Si esta en un estado de adquisición se adquieren los carácteres en el lugar correspondiente
    if((estado!=0)&&(inByte!='*')&&(inByte!=',')){
      SENSOR[estado-1][lugar]=inByte;
      lugar++;
    }
    if((inByte=='*')&&(estado!=0)){
      estado=-1;
      lugar=0;
      estado=10;
      SERIAL_CPU.print("&");
    }
    if((inByte==',')){
      estado++;
      lugar=0;
    }
    if(inByte=='G'){
      estado=1;
    }
  }
  /*
  if(estado==-1){
    // Se borra todo
    for(int i=0;i<6;i++){
      for(int j =0;i<5;j++){
        SENSOR[i][j]='\0';
      }
    }
    estado =0;
  }
  */
  //SERIAL_CPU.println(estado);
  //if(millis()-tiempo>5000){
  if(estado==10){
    estado=0;
    SERIAL_CPU.println(SENSOR[0]);
    SERIAL_CPU.println(SENSOR[1]);
    SERIAL_CPU.println(SENSOR[2]);
    SERIAL_CPU.println(SENSOR[3]);
    SERIAL_CPU.println(SENSOR[4]);
    SERIAL_CPU.println(SENSOR[5]);
    SERIAL_CPU.println("_");
    internet.mandarComandoATconRespuesta("AT+HTTPINIT\r\n");
    delay(10);
    internet.mandarCaracter("AT+HTTPPARA=\"URL\",\"http://kamani.solunes.com/api/reportar/cultivo-altiplano?presion=2&n1=1,");
    internet.mandarCaracter(SENSOR[0]);
    internet.mandarCaracter(",");
    internet.mandarCaracter(SENSOR[1]);
    internet.mandarCaracter(",");
    internet.mandarCaracter(SENSOR[2]);
    internet.mandarCaracter(",");
    internet.mandarCaracter(SENSOR[3]);
    internet.mandarCaracter(",");
    internet.mandarCaracter(SENSOR[4]);
    internet.mandarCaracter(",");
    internet.mandarCaracter(SENSOR[5]);
    internet.mandarCaracter("&n2=1,");
    internet.mandarCaracter(SENSOR[0]);
    internet.mandarCaracter(",");
    internet.mandarCaracter(SENSOR[1]);
    internet.mandarCaracter(",");
    internet.mandarCaracter(SENSOR[2]);
    internet.mandarCaracter(",");
    internet.mandarCaracter(SENSOR[3]);
    internet.mandarCaracter(",");
    internet.mandarCaracter(SENSOR[4]);
    internet.mandarCaracter(",");
    internet.mandarCaracter(SENSOR[5]);
    
    internet.mandarComandoATconRespuesta("\"");
    delay(10);
    internet.mandarComandoATconRespuesta("AT+HTTPACTION=0\r\n");
    delay(5000);
    internet.mandarComandoATconRespuesta("AT+HTTPREAD\r\n");
    delay(2000);
    internet.mandarComandoATconRespuesta("AT+HTTPTERM\r\n");
    delay(10);
    while(millis()-tiempo<1000){true;}
    
    SERIAL_CPU.print("Datos subidos a la nube ;-)\n");
    tiempo = millis();
    contador++;
    delay(4000);
 }
}

