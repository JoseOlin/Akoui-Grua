/* Este programa lee los botones y el joystick del Joystick Shield para controlar
 * la grúa.


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

  Los botones del joystick shield tienen resistencias pull-up, por lo tanto son activos
en bajo.
 El pin 12 no se utilizó como GPIO pues debe estar en LOW en el arranque, y los botones
tienen resistencias pull-up incorporadas.
 Se saltó el 12 y se usó el 15.

 El programa es para un ESP-WROM-32.
 + Placa:  ESP32 Arduino -> ESP32 Dev Module.

  NOTA: (Para usar la tarjeta hay que instalar las librerías manualmente).
*/


#include <WiFi.h>
#include <ArduinoHttpClient.h>

#include "JoystickShield.h"

const char* ssid = "GomezTorres";
const char* password = "lucy1nthesky";



HttpClient http;



unsigned int delayLoop = 5; // Procurar que la frecuencia del Pad sea el doble que la de la lectura en los módulos de movimiento.
unsigned int delayRequestParada = 5;

JoystickShield* joyShield;

void setup()
{
    Serial.begin(115200);

    joyShield = new JoystickShield();


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

    #if comHttpActiva
    Serial.println("La comunicación WiFi está activa, se enviarán peticiones Http a la Grúa.");
    #else
    Serial.println("La comunicación WiFi está inactiva (Modo de Pruebas), NO se enviarán peticiones Http a la Grúa.");
    #endif
}

void loop()
{
    joyShield.leerBotones();
    joyShield.leerJoystick();
    joyShield.validarEstadoBotones();

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


