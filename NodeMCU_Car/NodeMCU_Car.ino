#define ENA   14          // Enable/speed motor Derecha        GPIO14(D5)
#define ENB   12          // Enable/speed motor Izquierda         GPIO12(D6)
#define IN_1  15          // L298N in1 motor Derecha           GPIO15(D8)
#define IN_2  13          // L298N in2 motor Derecha           GPIO13(D7)
#define IN_3  2           // L298N in3 motor Izquierda            GPIO2(D4)
#define IN_4  0           // L298N in4 motor Izquierda            GPIO0(D3)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             //String de captura de comandos.
int velocidadAuto = 800;         // 400 - 1023.
int coeficiente_Velocidad = 3;

const char* ssid = "NodeMCU Car";
ESP8266WebServer server(80);

void setup() {
 
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
  
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void continuar(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, velocidadAuto);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, velocidadAuto);
  }

void irAtras(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, velocidadAuto);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, velocidadAuto);
  }

void irDerecha(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, velocidadAuto);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, velocidadAuto);
  }

void irIzquierda(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, velocidadAuto);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, velocidadAuto);
  }

void continuarDerecha(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, velocidadAuto/coeficiente_Velocidad);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, velocidadAuto);
   }

void continuarIzquierda(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, velocidadAuto);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, velocidadAuto/coeficiente_Velocidad);
  }

void irAtrasDerecha(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, velocidadAuto/coeficiente_Velocidad);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, velocidadAuto);
  }

void irAtrasIzquierda(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, velocidadAuto);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, velocidadAuto/coeficiente_Velocidad);
  }

void detenerRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, velocidadAuto);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, velocidadAuto);
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") continuar();
      else if (command == "B") irAtras();
      else if (command == "L") irIzquierda();
      else if (command == "R") irDerecha();
      else if (command == "I") continuarDerecha();
      else if (command == "G") continuarIzquierda();
      else if (command == "J") irAtrasDerecha();
      else if (command == "H") irAtrasIzquierda();
      else if (command == "0") velocidadAuto = 400;
      else if (command == "1") velocidadAuto = 470;
      else if (command == "2") velocidadAuto = 540;
      else if (command == "3") velocidadAuto = 610;
      else if (command == "4") velocidadAuto = 680;
      else if (command == "5") velocidadAuto = 750;
      else if (command == "6") velocidadAuto = 820;
      else if (command == "7") velocidadAuto = 890;
      else if (command == "8") velocidadAuto = 960;
      else if (command == "9") velocidadAuto = 1023;
      else if (command == "S") detenerRobot();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}







