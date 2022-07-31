/* Este sketch se programa en el ESP del módulo de control horizontal de la grúa
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>
// GPIO 0 y 2 son Normalmente Altos, así que se usará lógica con Activo en Bajo.
// NOTA: Poner el pin INV del puente MC33 en alto (puenteado con jumper) para que con IN1 e IN2 en alto, OUT1 y OUT2 estén en BAJO (GND).
#define pinIzquierda 0 //GPIO0 
#define pinDerecha 2  //GPIO2

//En caso de que no se use I2C ni UART, Tx y Rx pueden usarse como GPIO's (GPIO1 y GPIO3)
//#define limiteIzq 1   
//#define limiteDer 3

const char* ssid = "AkouiHor_AP";
const char* password = "lucy1nthesky";

/*const char* ssid = "VISION";
const char* password = "DNIE20A2#";
*/

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
WiFiClient client;

int flag_ParoEmerg = 0;

// Dirección actual de la grúa.
boolean flagMoverIzq = 0, flagMoverDer = 0;
int valorLimiteIzq, valorLimiteDer;
String req, s;

void setup() {
  Serial.begin(115200);
  delay(10); 
    // Configurar GPIO0. Por defecto en Alto
  pinMode(pinIzquierda, OUTPUT);
  //digitalWrite(pinIzquierda, LOW);
  digitalWrite(pinIzquierda, HIGH); //Activo en BAJO, inactivo en ALTO.

  // Configurar GPIO2. Por defecto en Alto.
  pinMode(pinDerecha, OUTPUT);
  //digitalWrite(pinDerecha, LOW);
  digitalWrite(pinDerecha, HIGH);

  //Pines para los limits switch //(Tx y Rx).
  // Configurar GPIO1
  // pinMode(limiteIzq, INPUT);
  // Configurar GPIO3
  // pinMode(limiteDer, INPUT);
  
  
  // Connect to WiFi network
  Serial.print("Setting Access Point ");
  Serial.println(ssid);
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
 
  // Start the server
  server.begin();
  Serial.println("Servidor inicializado");

  delay(1500); 
}

void controlMotor()
{
  // Aplicar lógica de activo en bajo.
  flagMoverIzq = !flagMoverIzq;
  flagMoverDer = !flagMoverDer;
  
  // Set GPIO0 de acuerdo a la solicitud y Paro de Emergencia
  digitalWrite(pinIzquierda, flagMoverIzq);
  //Serial.print("flagDirIzq: "); Serial.println(flagMoverIzq);
  
  // Set GPIO2 de acuerdo a la solicitud y Paro de Emergencia
  digitalWrite(pinDerecha, flagMoverDer);
  //Serial.print("flagDirDer: "); Serial.println(flagMoverDer);
}


void loop() {
  
  //valorLimiteIzq = digitalRead(limiteIzq); // Normalmente ALTO. Activos en BAJO
  //valorLimiteDer = digitalRead(limiteDer);
  //delay(1);
  
  // Check if a client has connected
  client = server.available();  // Listen for incoming clients
  
  if (!client)
  {
    // Si no hay cliente conectado detener el movimiento del motor.
    flagMoverIzq = 0; 
    flagMoverDer = 0;
    /*if(valorLimiteIzq == 0) 
    {
      flagDirIzq = 0;  
      digitalWrite(pinIzquierda, 0);
    }
    if(valorLimiteDer == 0)
    {
      flagDirDer = 0;    
      digitalWrite(pinDerecha, 0);
    }*/ 
    controlMotor();
    
    return;
  }
  
  // Wait until the client sends some data  
  while(!client.available()){  
    flagMoverIzq = 0; 
    flagMoverDer = 0;
    controlMotor();
    
    delay(1); // Verificar si esto se ejecuta.
  }
  
  // Read the first line of the request
  req = client.readStringUntil('\r'); // Leer hasta salto de línea.
  Serial.println(req);
  client.flush();

  // TODO: Implementar Server en Modo AP.

  // Verificar Paro de Emergencia
  if (req.indexOf("/paro/0") != -1){
    flag_ParoEmerg = 0;    // Paro de Emergencia Activado
    //client.stop();
    //return;
  }
  if (req.indexOf("/paro/1") != -1){
    flag_ParoEmerg = 1;   // Paro de Emergencia Desactivado
  }

  // Realizar acción considerando el Paro de Emergencia
  if (flag_ParoEmerg) // flag_ParoEmergencia = 1: DESACTIVADO. Si el Paro de Emergencia está Desactivado. flag_ParoEmerg es Activo en Alto.
  { 
    
      // En esta sección se aplica lógica de activo en Alto, que es más fácil de revisar; en controlMotor se invierte.
      if (req.indexOf("/izquierda/0") != -1) // Si aparece la cadena /izquierda/0 al menos una vez.
      {
        flagMoverIzq = 0; 
        flagMoverDer = 0;
      }
      else if (req.indexOf("/izquierda/1") != -1)
      {
        /*if(valorLimiteIzq == 1)
        {*/
          flagMoverIzq = 1;
          flagMoverDer = 0;
         /*}
        else
        {
          flagMoverIzq = 0;   flagMoverDer = 0;
        }*/
      }
      else if (req.indexOf("/derecha/0") != -1)
      {
        flagMoverIzq = 0;
        flagMoverDer = 0;
      }
      else if (req.indexOf("/derecha/1") != -1)
      {
        /*if(valorLimiteDer == 1)
        {*/  
          flagMoverIzq = 0;
          flagMoverDer = 1; 
        /*}
        else
        { 
          flagMoverIzq = 0;  flagMoverDer = 0;
        }*/
      }
      else  
      {
        flagMoverIzq = 0;
        flagMoverDer = 0;
      }
  }
  else // flag_ParoEmergencia = 0: ACTIVADO.
  {
    flagMoverIzq = 0;
    flagMoverDer = 0;
  }

   // Si ambas banderas de dirección están activas, desactivarlas ambas.
  if((flagMoverIzq == 1) && (flagMoverDer == 1))
  {
    flagMoverIzq = 0;
    flagMoverDer = 0;
  }
  
  controlMotor();

   client.flush();

  // Prepare the response
  s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  if(flagEmerg == 1){
    s += "GPIO0:";
    s += (flagMoverIzq) ? "alto" : "bajo";
    s += "\nGPIO2:";
    s += (flagMoverDer) ? "alto" : "bajo";
  }
  else if(flagEmerg == 0) {
    s += "Paro de Emergencia está activado.";
  }
  
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Cliente desconectado");
  s = "";
  req = "";

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
  
  client.flush();
  delay(10);
 
}
