#include "CommTCP.h"

CommTCP::CommTCP()
{
    WiFi.begin(ssid, password);

    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());

    serverH->begin();
    //serverV->begin();
}


void CommTCP::TCPEcho()
{
    clientH = serverH->available();


    if(clientH)
    {
        if (clientH.connected())
        {
            Serial.println("Connected to client");
        }

        if (clientH.available() > 0)
        {
            // Read incoming message
            char inChar = clientH.read();

            // Send back something to the client
            serverH->write(inChar);
            // Echo input on Serial monitor
            Serial.write(inChar);
        }
    }
}

void CommTCP::sendCommand(String serverS, const String command)
{
    if(serverS == "H")
    {
        clientH = serverH->available();
        if(clientH)
        {
            if (clientH.connected())
            {
                Serial.println("Connected to client");
                serverH->print(command);
            }
        }
    }
    else if (serverS = "V")
    {

    }
}

/*void httpRequest(String serverPath)
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

    #if commVerbose
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
}*/


