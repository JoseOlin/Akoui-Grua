/* Este sketch se programa en el ESP del módulo de control horizontal de la grúa
 *  
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/paro/0 will set the GPIO2 low,
 *    http://server_ip/paro/1 will set the GPIO2 high
 *    http://server_ip/izquierda/1
 *     http://server_ip/derecha/1
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 *  
 *  
 *  The ESP-01 board can be set as AP (no modem needed) or Station (Modem needed).
 *  This is Station version. 
 *  
 *  Placa (ESP-01): 
 *  ESP8266 Boards (2.7.4) -> Generic ESP8266 Module  
 */

#include <ESP8266WiFi.h>
// GPIO 0 y 2 son normalmente altos, así que se usará lógica con activo en bajo.
// NOTA: Poner el pin INV del puente MC33 en alto (puenteado con jumper) para que con IN1 e IN2 en alto, OUT1 y OUT2 estén en BAJO (GND).
#define pinIzquierda 0 //GPIO0 
#define pinDerecha 2  //GPIO2

//En caso de que no se use I2C ni UART, Tx y Rx pueden usarse como GPIO's (GPIO1 y GPIO3)
//#define limiteIzq 1   
//#define limiteDer 3

const char* ssid = "GomezTorres";
const char* password = "lucy1nthesky";

#define DEBUG_MOVIMIENTO 1
#define DEBUG_COM 1
#define ACTIVE_ON_HIGH 1 //Logic for the DC driver.

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
WiFiClient client;

int flag_ParoEmerg = 0;

// Dirección actual de la grúa.
boolean flagMoverIzq = 0, flagMoverDer = 0;
int valorLimiteIzq, valorLimiteDer;
String req, s;

// Variables to stop when no client available (safety reasons)
unsigned int contNoClient = 0; 
unsigned int delayNoClient = 50; // ms
unsigned int delayClientNoAvailable = 5; // ms
unsigned int delayLoopClient = 10; // ms
unsigned int maxTiempoActivo = 3000;// ms
unsigned int umbralContNoClient = maxTiempoActivo / delayNoClient;


void setup() {
  Serial.begin(115200);
  
  /* The pin configuration is for MC33296 driver correspondence*/
    // Configurar GPIO0 y GPIO2
  pinMode(pinIzquierda, OUTPUT);
  pinMode(pinDerecha, OUTPUT);
  
  #if ACTIVE_ON_HIGH
    digitalWrite(pinIzquierda, LOW);
    digitalWrite(pinDerecha, LOW);
  #else // Active on LOW.
    digitalWrite(pinIzquierda, HIGH); // Activo en BAJO, inactivo en ALTO.
    digitalWrite(pinDerecha, HIGH);
  #endif  

  delay(10); 
  // Pines para los limits switch //(Tx y Rx).
  // Configurar GPIO1
  // pinMode(limiteIzq, INPUT);
  // Configurar GPIO3
  // pinMode(limiteDer, INPUT);
  
  
  // Connect to WiFi network
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado\n\n");
  
  // Start the server
  server.begin();
  Serial.println("Servidor inicializado");

  // Print the IP address
  Serial.println(WiFi.localIP());

  Serial.print("Maximo tiempo Activo: ");
  Serial.println(maxTiempoActivo);
 
  Serial.print("Umbral Contador No Client: ");
  Serial.println(umbralContNoClient);
  
  delay(1500); 
}

void controlMotor()
{
  // The rest of the code use Active on High Logic for readability, only here in inverted 
  // when the Active on High logic is activated.
  #if ACTIVE_ON_HIGH
    
  #else
    // Aplicar lógica de activo en bajo.
    flagMoverIzq = !flagMoverIzq;
    flagMoverDer = !flagMoverDer;
  #endif
  
  // Set GPIO0 de acuerdo a la solicitud y Paro de Emergencia
  digitalWrite(pinIzquierda, flagMoverIzq);
  //Serial.print("flagDirIzq: "); Serial.println(flagMoverIzq);
  
  // Set GPIO2 de acuerdo a la solicitud y Paro de Emergencia
  digitalWrite(pinDerecha, flagMoverDer);
  //Serial.print("flagDirDer: "); Serial.println(flagMoverDer);
}


void loop() 
{  
  //valorLimiteIzq = digitalRead(limiteIzq); // Normalmente HIGH. LOW cuando se activan.
  //valorLimiteDer = digitalRead(limiteDer);

  // Check if a client has connected
  client = server.available();

  if (!client)
  {
    // Si no hay cliente conectado detener el movimiento del motor.
    contNoClient++;
    if(contNoClient == umbralContNoClient)
    {
    
      #if DEBUG_COM
        Serial.println("Deteniendo por !client");
      #endif
      
      flagMoverIzq = 0; 
      flagMoverDer = 0;
      
      controlMotor();  
      //contNoClient = 0; // Esta se reinicia cuando haya un nuevo cliente.
    }
    
    delay(delayNoClient);
    return; // Volver a iniciar el loop().
  }

#if DEBUG_COM
  //Serial.println("New client");
#endif  

  // Wait until the client sends some data  
  while(!client.available())
  {
    delay(delayClientNoAvailable); 
    
    #if DEBUG_COM
      Serial.println("!client.availble()");
    #endif
  }

  contNoClient = 0;  
  
  // Read the first line of the request
  req = client.readStringUntil('\r'); // Leer hasta salto de línea.

#if DEBUG_COM
  //Serial.println(req);
#endif

  client.flush();

  // Verificar Paro de Emergencia
  if (req.indexOf("/paro/0") != -1){
    flag_ParoEmerg = 0;    // Paro de Emergencia Desactivado
    #if DEBUG_MOVIMIENTO
    Serial.println("Paro de Emergencia Desactivado");
    #endif
    //client.stop();
    //return;
  }
  if (req.indexOf("/paro/1") != -1){
    flag_ParoEmerg = 1;   // Paro de Emergencia Activado
    #if DEBUG_MOVIMIENTO
    Serial.println("Paro de Emergencia Activado");
    #endif
  }

  // Realizar acción considerando el Paro de Emergencia
  if (!flag_ParoEmerg) // Si el Paro de Emergencia está Desactivado.
  {     
      // En esta sección se aplica lógica de activo en Alto, que es más fácil de revisar; en controlMotor se invierte.   
      
      if (req.indexOf("/izquierda/1") != -1)
      { // Iniciar el movimiento hacia la izquierda.
        /*if(valorLimiteIzq == 1) {*/
          flagMoverIzq = 1;
          flagMoverDer = 0;
          
          #if DEBUG_MOVIMIENTO
          Serial.println("Moviendo izq.");
          #endif
         /*} else {
          flagMoverIzq = 0;   flagMoverDer = 0;
        }*/
      }
      
      else if (req.indexOf("/derecha/1") != -1)
      {
        /*if(valorLimiteDer == 1) {*/  
          flagMoverIzq = 0;
          flagMoverDer = 1; 
          #if DEBUG_MOVIMIENTO
          Serial.println("Moviendo der.");
          #endif
        /*} else { 
          flagMoverIzq = 0;  flagMoverDer = 0;
        }*/
      }
      else if (req.indexOf("/izquierda/0") != -1) // Si aparece la cadena /izquierda/0 al menos una vez.
      { // Detener el movimieto hacia la izquierda.
        flagMoverIzq = 0; 
        flagMoverDer = 0;
        
        #if DEBUG_MOVIMIENTO
        Serial.println("Detener mov. izq.");
        #endif
      }
      else if (req.indexOf("/derecha/0") != -1)
      { // Detener el movimiento hacia la derecha.
        flagMoverIzq = 0;
        flagMoverDer = 0;
        
        #if DEBUG_MOVIMIENTO
        Serial.println("Detener mov. der.");
        #endif
      }
  }
  else // flag_ParoEmergencia = 1: ACTIVADO.
  {
    flagMoverIzq = 0;
    flagMoverDer = 0;
    
    #if DEBUG_MOVIMIENTO
      Serial.println("Paro de Emergencia Activado.");
    #endif

  }

   // Si ambas banderas de dirección están activas, desactivarlas ambas.
  if((flagMoverIzq == 1) && (flagMoverDer == 1))
  {
    flagMoverIzq = 0;
    flagMoverDer = 0;
  }
  
  controlMotor();

  // Prepare the response
  s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  if(flag_ParoEmerg == 0){
    s += "flagMoverIzq: ";
    s += (flagMoverIzq) ? "alto" : "bajo";
    s += "\flagMoverDer: ";
    s += (flagMoverDer) ? "alto" : "bajo";
  }
  else if(flag_ParoEmerg == 1) {
    s += "Paro de Emergencia Activado.";
  }
  
  s += "</html>\n";

  // Send the response to the client
  client.print(s);  
  s = "";
  req = "";

#if DEBUG_COM
  //Serial.println("Cliente desconectado");
#endif
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
  
  client.flush();

  delay(delayLoopClient);
}
