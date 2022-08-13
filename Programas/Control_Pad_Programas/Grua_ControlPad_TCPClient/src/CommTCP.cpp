#include "CommTCP.h"

CommTCP::CommTCP()
{
    WiFi.begin(ssid, password);

    Serial.print("Connecting to "); Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());


    //int maxClients = 4;
    //Serial.println("Creating ServerV");
    //IP_Ver = IPAddress(192, 168, 1, 69);
    //serverV = new WiFiServer(IP_Ver, puertoV, maxClients);
    //serverV->begin();
#if CASA
    Serial.print("Akoui_Ver: "); Serial.print(IPVerHost); Serial.print(", Puerto: "); Serial.println(puertoV);
#endif
    //Serial.println("Creating ServerH");
    //IP_Hor = IPAddress(192, 168, 1, 88); //TODO: Check IP_Hor
    //serverH = new WiFiServer(IP_Hor, puertoH, maxClients);
    //serverH->begin();
    Serial.print("Akoui_Hor: "); Serial.print(IPHorHost); Serial.print(", Puerto: "); Serial.println(puertoH);


    Serial.println("Connecting ClientV");
    //clientV = serverV->available();
    #if CASA
    clientV.connect(IPVerHost, puertoV);
    int contV = 0;
    while(!clientV.connected())
    {
        //clientV = serverV->available();

        /*if(clientV.connected())
        {
            Serial.println("ClientV connected");
            break;
        }*/
        Serial.print(".");
        delay(500);

        contV++;
        if(contV > 8)
        {
            Serial.println("ClientV not responding");
            break;
        }
    }
    #endif

    Serial.println("Connecting ClientH");
    //clientH = serverH->available();
    clientH.connect(IPHorHost, puertoH);
    int contH = 0;
    while(!clientH.connected())
    {
        Serial.print(".");
        delay(500);
        contH++;
        if(contH > 8)
        {
            Serial.println("ClientH not responding");
            break;
        }
    }

}

/*
void CommTCP::TCPEcho()
{
    //clientH = serverH->available();


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
}*/

void CommTCP::sendCommand(String hostKey, String command)
{
    if(hostKey == "H")
    {
        //clientH = serverH->available();
        if(clientH)
        {
            if (clientH.connected())
            {
                Serial.println("clientH Connected.");
                //serverH->print(command);
                clientH.print(command);
            }
            else
            {
                Serial.println("clienteH not connected.");
            }
        }
        else
        {

        }
    }
    else if (hostKey == "V")
    {
        //clientV = serverV->available();
        if(clientV)
        {
            if (clientV.connected())
            {
                #if commVerbose
                Serial.println(", ClientV Connected");
                #endif
                //serverV->print(command);
                #if commActiva
                clientV.print(command);
                //clientV.write(command);
                #endif
            }
            else
            {
                Serial.println("clienteV not connected.");
            }
        }
        else
        {
            Serial.println("!clienteV");
        }
    }
    else
    {
        Serial.println("Host Key not valid.");
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


