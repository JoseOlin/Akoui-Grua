/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,  
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

// Los pines GPI0 y GPI2 son pines digitales.
#define pinBajar 0
#define pinSubir 2

// Si no se usará comunicación, los pines 1 y 3 pueden usarse como GPIO
#define pinParo 1
#define pinBlancoNegro 3 // Cuando la grúa se mueve en un sentido, este pin también debe activarse
// En el programa se activa con cualquier dirección y no afecta, aunque en el diagrama sólo se activaba en una dirección...
// TODO: Revisar la documentación de la grúa para ver la función de este pin.

const char* ssid = "GomezTorres";
const char* password = "lucy1nthesky";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
WiFiClient client;

int flagParoEmerg = 0;
int flagSubiendo, flagBajando;
String req, s;

void setup() {
  // Los pines del ESP tienen lógica de activo en bajo. (Resistencia pull-up)
  //Serial.begin(115200);// Cuando se usan los pine 1 y 3 se desactiva la comunicación serial.
  
  // Configurar GPIO0
  pinMode(pinBajar, OUTPUT);
  digitalWrite(pinBajar, 1);
  
  // Configurar GPIO1
  pinMode(pinParo, OUTPUT);
  digitalWrite(pinParo, 1); 

  // Configurar GPIO2
  pinMode(pinSubir, OUTPUT);
  digitalWrite(pinSubir, 1);

  // Configurar GPIO3
  pinMode(pinBlancoNegro, OUTPUT);
  digitalWrite(pinBlancoNegro, 1);  

  
  //Serial.print("Conectando a ");
  //Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Iniciar el servidor
  server.begin();

  Serial.println(WiFi.localIP());
  
}

void loop() {
  
  // Verificar si el cliente se ha conectado
  client = server.available();
  if (!client) {
    return;
  }
  
  // Esperar hasta que el cliente envie algo de datos
  while(!client.available()){
    delay(1);
  }
  
  // Leer la primera linea de solicitud
  req = client.readStringUntil('\r');
  client.flush();

  // Verificar Paro de Emergencia
  if (req.indexOf("/paro/0") != -1)
  {
    Serial.println("Paro Emergencia Desactivado");
    flagParoEmerg = 0;    
  }
  if (req.indexOf("/paro/1") != -1){
    Serial.println("Paro Emergencia Activado");
    flagParoEmerg = 1;
    //client.stop();
    ///return;
  }

  // Realizar acción considerando el Paro de Emergencia
  if (flagParoEmerg == 0)
  {
    if ( req.indexOf("/subir/1") != -1 )
    {
      Serial.println("Subiendo");
      digitalWrite(pinSubir, 0);
      flagSubiendo = 1;
    }
    else if (req.indexOf("/subir/0") != -1)
    {
      Serial.println("Deteniendo subida");
      digitalWrite(pinSubir, 1); 
      flagSubiendo = 0;
    }
     
    else if (req.indexOf("/bajar/1") != -1)
    {
      Serial.println("Bajando");
      digitalWrite(pinBajar, 0);
      flagBajando = 1;
    }
    else if (req.indexOf("/bajar/0") != -1)
    {
      Serial.println("Deteniendo bajada");
      digitalWrite(pinBajar, 1);
      flagBajando = 0;
    }
    /*else{    
      client.stop();
      return;
    }*/
  } 
  else { //Paro Emergencia == 1
    Serial.print("Se activó el paro de emergencia");
    digitalWrite(pinParo, 0); //Normalmente altos, activos en bajo.
    digitalWrite(pinSubir, 1);
    digitalWrite(pinBajar, 1);
    //flagSubiendo = 0;
    //flagBajando = 0;
  }

  if((flagSubiendo == 1) && (flagBajando == 1)){
    flagSubiendo = 0;
    flagBajando = 0;
    Serial.println("sub==1 && baj == 1");
  }
  
  if( (flagBajando == 1 || flagSubiendo == 1) && flagParoEmerg == 0)
  {
    Serial.println("B-N 0");
    digitalWrite(pinBlancoNegro, 0);
  } 
  else { // Si ambos movimientos desactivados o el Paro Activado.
    Serial.println("B-N 1");
    digitalWrite(pinBlancoNegro, 1);  
  }
  
  client.flush();
  // Preparar la respuesta
  s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "El paro de emergencia está ";
  s += (flagParoEmerg) ? "activado." : "desactivado.";
//  if(flagEmerg == 0){
//    s += "GPIO0 esta en ";
//    s += (flagBaj)?"alto":"bajo";
//    s += "\nGPIO2 esta en ";
//    s += (flagSub)?"alto":"bajo";
//  }
//  else if(flagEmerg == 1){
//    s += "Esta presionado el Paro de Emergencia";
//  }
  
  s += "</html>\n";

  // Enviar respuesta al cliente
  client.print(s);
  delay(1);
  s = "";
  req = "";
  
  client.flush();
}
