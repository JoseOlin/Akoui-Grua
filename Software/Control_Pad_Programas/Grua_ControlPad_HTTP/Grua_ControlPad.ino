/* Este programa lee los botones y el joystick del Joystick Shield para controlar la grúa. 


 Los números de pin corresponden con el número de GPIO en el WROOOM (morados en el pinOut), 
que corresponde con la etiqueta en la tablilla (D13 = GPIO13, etc.)

Los pines digitales en el Joystick Shield (no etiquetados) tienen la siguiente configuración
  A
D   B
  C

Su conexión al ESP32 WROOM es la siguiente
 F  E   D  C  B   A 
 A: 13
 B: 15
 C: 14
 D: 27
 E: 33 
 F: 32

 X: 35 
 Y: 34
 K: No conectado, es el botón del joystick.

  Los botones del joystick shield tienen resistencias pull-up, por lo tanto son activos en bajo.
 El pin 12 no se utilizó como GPIO pues debe estar en LOW en el arranque, y los botones tienen resistencias pull-up incorporadas.
 Se saltó el 12 y se usó el 15.

 El programa es para un ESP-WROM-32. 
 + Placa:  ESP32 Arduino -> ESP32 Dev Module.
  
  NOTA: (Para usar la tarjeta hay que instalar las librerías manualmente).
*/

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "GomezTorres";
const char* password = "lucy1nthesky";

String serverNameV = "http://192.168.1.69"; // Dirección del ESP para el movimiento vertical
String serverNameH = "http://192.168.1.70"; // Dirección del ESP para el movimiento horizontal

HTTPClient http;


int pinSubir = 13; //C
int pinBajar = 14; //A

int pinIzquierda = 27; //D
int pinDerecha = 15;  //B 

int pinParo = 16; // K

int pinDAC1 = 25; 
int pinDAC2 = 26;

int pinAbrirPinza = 32; //
int pinCerrarPinza = 33; //

int pinJx = 35;
int pinJy = 34;

int Jx_Centro = 1850;
int Jy_Centro = 1870;

int umbralLecturaJoystick = 250;


boolean flagSubiendo = false, flagBajando = false;
boolean flagMoviendoIzq = false, flagMoviendoDer = false;
boolean flagAbriendo = false, flagCerrando = false;
boolean flagParo = false;

unsigned long tiempoUltimaPulsacionParo = 0;
unsigned long umbralLecturaParo =  1000; // El botón de paro se leerá cada 1000 ms.
unsigned int delayLoop = 5; // Procurar que la frecuencia del Pad sea el doble que la de la lectura en los módulos de movimiento.
unsigned int delayRequestParada = 5;

#define comActiva 1
#define comVerbose 1

void setup() 
{
  Serial.begin(115200);
  
  pinMode(pinSubir, INPUT);
  pinMode(pinBajar, INPUT);
  pinMode(pinIzquierda, INPUT);
  pinMode(pinDerecha, INPUT);

  pinMode(pinCerrarPinza, INPUT);
  pinMode(pinAbrirPinza, INPUT);

  pinMode(pinParo, INPUT);
  
  
  http.setConnectTimeout(500); //Tiempo en milisegundos.
   
  WiFi.begin(ssid, password);

  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  #if comActiva
  Serial.println("La comunicación WiFi está activa, se enviarán peticiones Http a la Grúa.");
  #else
  Serial.println("La comunicación WiFi está inactiva (Modo de Pruebas), NO se enviarán peticiones Http a la Grúa.");
  #endif
}
 
void loop() 
{
  leerBotones();
  leerJoystick();
  
  delay(delayLoop);
}

void httpRequest(String serverPath)
{
  //int umbralIntentos = 5;
  //int contIntentos = 0;
  if(WiFi.status()== WL_CONNECTED)
  {
    int httpResponseCode;    
                      // IP + path
    if(http.begin(serverPath.c_str() ) )
    {
      http.setConnectTimeout(500);

      //do
      //{
        // Enviar la petición http.
      httpResponseCode = http.GET();

        //contIntentos++;
      //} while(httpResponseCode < 0 || contIntentos < umbralIntentos);    

      #if comVerbose
      if(httpResponseCode > 0)
      {
        String payload = http.getString();
        Serial.println(payload);
      }
      else
      {
        //Serial.print("HTTP GET error ");
        //Serial.println(http.errorToString(httpResponseCode).c_str());
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
      }
      #endif
             
      http.end();
    }
    else
    {
      Serial.println("HTTP unable to connect");
    }
  }
  else{
    Serial.println("No hay conexión");
  }
}

void leerBotones()
{
  // Los botones tienen resistencias pull-up, por lo tanto están activos en Bajo.
  
  int subir = digitalRead(pinSubir);
  int bajar = digitalRead(pinBajar);
  int izquierda = digitalRead(pinIzquierda);
  int derecha = digitalRead(pinDerecha);
  
  int cerrar = digitalRead(pinCerrarPinza);
  int abrir = digitalRead(pinAbrirPinza);

  int paro = digitalRead(pinParo);


  /*if(subir == LOW && !flagSubiendo)
  {
    Serial.println("Activando subida...");
    String subir_activar = serverNameV + "/subir/1";
    //httpRequest(subir_activar);
    flagSubiendo = true;
  }
  else if(subir == HIGH && flagSubiendo)
  {
    Serial.println("Desactivando subida...");
    String subir_desactivar = serverNameV + "/subir/0";
    //httpRequest(subir_desactivar);
    //httpRequest(subir_desactivar);
    flagSubiendo = false;
  }*/

  // Hay tres tipos de validación para el estado de los botones.
  // - Pulso en dos sentidos (presionar y liberar), 
  // - Pulso Escalón (enviar mientras está en alto) y 
  // - Pulso con un sentido (Activa y desactiva con el mismo flanco).
  
  validarEstadoBoton(subir, flagSubiendo, serverNameV, "/subir/");
  validarEstadoBoton(bajar, flagBajando, serverNameV, "/bajar/");
    
  validarEstadoBoton(izquierda, flagMoviendoIzq, serverNameH, "/izquierda/");
  validarEstadoBoton(derecha,   flagMoviendoDer, serverNameH, "/derecha/");
  
  //validarEstadoBoton_Continuo(izquierda, serverNameH, "/izquierda/");
  //validarEstadoBoton_Continuo(derecha, serverNameH, "/derecha/");

  validarBotones_Pinza(abrir,  flagAbriendo, "Abrir");
  validarBotones_Pinza(cerrar, flagCerrando, "Cerrar");


  validarBoton_Paro(paro, flagParo);  
}

void validarEstadoBoton(int &estado, bool &flagActivo, const String serverName, String comando)
{
  if(estado == LOW && !flagActivo)
  {
    #if comVerbose
    Serial.print("Activando "); Serial.println(comando);
    #endif
    
    String comando_Activar = serverName + comando + "1";
    #if comActiva
    httpRequest(comando_Activar);
    #endif
    flagActivo = true;
  }
  else if(estado == HIGH && flagActivo)
  {
    #if comVerbose
    Serial.print("Desactivando "); Serial.println(comando);
    #endif
    
    String comando_Desactivar = serverName + comando + "0";
    
    #if comActiva
    httpRequest(comando_Desactivar);
    delay(delayRequestParada);
    
    httpRequest(comando_Desactivar);
    delay(delayRequestParada);
    
    httpRequest(comando_Desactivar);
    #endif
    
    flagActivo = false;

    //TODO: Probar si es mejor implementar un contador y enviar un Request por ciclo del loop.
  }
}


void validarEstadoBoton_Continuo(int &estado, const String serverName, String comando)
{
  if(estado == LOW)
  {
    Serial.print("Activando "); Serial.println(comando);
    String comando_Activar = serverName + comando + "1";
    #if comActiva
    httpRequest(comando_Activar);
    #endif
  }
  /*else if(estado == HIGH)
  {
    Serial.print("Desactivando "); Serial.println(comando);
    String comando_Desactivar = serverName + comando + "0";
    #if comActiva
    httpRequest(comando_Desactivar);
    #endif
  }*/
}

void validarBotones_Pinza(int estado, bool &flagActivo, String comando)
{
  if(estado == LOW && !flagActivo)
  {
    Serial.print("Activando "); Serial.println(comando);
    //String comando_Activar = serverName + comando + "1";
    flagActivo = true;
  }
  else if(estado == HIGH && flagActivo)
  {
    Serial.print("Desactivando "); Serial.println(comando);
    //String comando_Activar = serverName + comando + "0";
    flagActivo = false;
  }
}


void validarBoton_Paro(int estado, bool &flagActivo)
{
  // La activación y desactivación del paro es con la misma acción del botón, así que debe validarse que una vez leído, el 
  // botón no se vuelva a leer durante cierto periodo.
  unsigned long tiempoActual = millis();
  unsigned long tiempoTranscurrido = tiempoActual - tiempoUltimaPulsacionParo;
  
  if(estado == LOW && flagActivo == false && (tiempoTranscurrido > umbralLecturaParo) )
  {
    String comandoActivarParo_V = serverNameV + "/paro/1";
    String comandoActivarParo_H = serverNameH + "/paro/1";
    Serial.println("Activando paro de emergencia");
     #if comActiva
    httpRequest(comandoActivarParo_V);
    delay(10);
    httpRequest(comandoActivarParo_V);
    
    httpRequest(comandoActivarParo_H);
    delay(10);
    httpRequest(comandoActivarParo_H);
    #endif
    flagActivo = true;
    tiempoUltimaPulsacionParo = millis();
  }
  else if(estado == LOW && flagActivo == true && tiempoTranscurrido > umbralLecturaParo)
  {
    String comandoDesactivarParo_V = serverNameV + "/paro/0";
    String comandoDesactivarParo_H = serverNameH + "/paro/0";
    Serial.println("Desactivando paro de emergencia");
     #if comActiva
    httpRequest(comandoDesactivarParo_V);
    httpRequest(comandoDesactivarParo_H);
    #endif
    flagActivo = false;
    tiempoUltimaPulsacionParo = millis();
  }
}

void leerJoystick()
{
  int JxVal = analogRead(pinJx);
  int JyVal = analogRead(pinJy);

  int JxAbsDif = abs(Jx_Centro - JxVal);
  int JyAbsDif = abs(Jy_Centro - JyVal);
  
  if(JxAbsDif > umbralLecturaJoystick || JyAbsDif > umbralLecturaJoystick)
  {
    Serial.print("Jx: "); Serial.print(JxVal);
    Serial.print(",\tJy: "); Serial.println(JyVal);
  } 
}
