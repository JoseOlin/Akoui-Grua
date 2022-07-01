/* Servidor TCP en ESP-01
 *
 * Recursos/Electronica/Tarjetas_Desarrollo/ESP/Programas_Ejemplo/ServidorClienteTCP_ServidorESP_ClienteQT/ServidorTCP_ESP/
 */

#include <ESP8266WiFi.h>

#define DEBUG_COMM 1
#define BOOT_MESSAGES 1

int port = 8888;  //Port number
WiFiServer server(port);

WiFiClient client;

//Server connect to WiFi Network
const char *ssid = "GomezTorres";  // Enter your wifi SSID
const char *password = "lucy1nthesky";  // Enter your wifi Password

long currentTime, lastTime;
long targetPeriod = 50;
long messagesPeriod = 500;

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA); // Configurar como Station (Instead of Acces Point)
    WiFi.begin(ssid, password); // Connect to WiFi


    // Wait for connection
#if BOOT_MESSAGES
    Serial.println("Boot delay");
    delay(2000);
    Serial.println("Connecting to Wifi");
#endif
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
      delay(500);
    }

#if BOOT_MESSAGES
    Serial.println("");
    Serial.print("Conectado a ");
    Serial.println(ssid);

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
#endif

    server.begin();

#if BOOT_MESSAGES
    Serial.print("Open TCP socket and connect to IP:");
    Serial.print(WiFi.localIP());
    Serial.print(" on port ");
    Serial.println(port);
#endif
    lastTime = millis();
}

void loop()
{
    currentTime = millis();
    if( (lastTime - currentTime) > messagesPeriod)
    {
        Serial.print(".");
    }

    client = server.available();
    if(client)
    {
        if(client.connected())
        {
          Serial.println("Client Connected");
        }

        // The client will be the Control pad or the Android App
        while(client.connected())
        {
            while(client.available() > 0)
            {
                // read data from the connected client
                char car = client.read();
                Serial.write(car);
            }

            //Send Data to connected client
            while(Serial.available() > 0)
            {
                char car = Serial.read();
                client.write(car);
            }
        }

        client.stop();

        Serial.println("Client disconnected");
    }
}
