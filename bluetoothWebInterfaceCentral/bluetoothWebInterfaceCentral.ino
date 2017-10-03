// Arduino Mega

#define SERIAL_CPU Serial
#define SERIAL_EMB Serial1
#define SERIAL_BTH Serial2
//#define SERIAL_SIM Serial3 /Ya definida en la libreria sim800basic

#include <sim800basic.h>

SIM800basic internet(3,9600,0);


int inByte;
int simByte;
unsigned long tiempo;
int contador=0;


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
  delay(10);
  internet.mandarComandoATconRespuesta("AT+SAPBR=3,1,\"USER\",\"VIVAINTERNET\"\r\n");
  delay(10);
  internet.mandarComandoATconRespuestaEspera("AT+SAPBR=1,1\r\n",20);
  delay(2000);
  tiempo = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (SERIAL_EMB.available()) {
    inByte = SERIAL_EMB.read();
    SERIAL_BTH.write(inByte);
    SERIAL_CPU.write(inByte);
    if(estado==1){
      L[]
    }
    if(inByte=='G'){
      estado=1
    }
  }
  if(millis()-tiempo>5000){
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
 }
}
