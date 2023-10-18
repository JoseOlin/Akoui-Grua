#include "CommTCP.h"

CommTCP::CommTCP(int pinWifiConn, int pinSocketVerConn, int pinSocketHorConn)
{
    WiFi.begin(ssid, password);

    Serial.print("Connecting to "); Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    wifiConnected_flag = true;
    digitalWrite(pinWifiConn, wifiConnected_flag);

    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());

#if CASA
    Serial.print("Akoui_Ver: "); Serial.print(IPVerHost);
    Serial.print(", Puerto: "); Serial.println(puertoV);
    Serial.println("Connecting ClientV...");
    clientV.connect(IPVerHost, puertoV);

    int clientV_connTrialsCounter = 0;
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

        clientV_connTrialsCounter++;
        if(clientV_connTrialsCounter > 8)
        {
            Serial.println("ClientV not responding");
            break;
        }
    }
    if(clientV_connTrialsCounter <= 8) // If less than 8 it get connected.
    {
        Serial.println("ClientV Connected");
        clientVConnected_flag = true;
        digitalWrite(pinSocketVerConn, clientVConnected_flag);
    }
#endif

    Serial.print("Akoui_Hor: "); Serial.print(IPHorHost);
    Serial.print(", Puerto: "); Serial.println(puertoH);
    Serial.println("Connecting ClientH");
    clientH.connect(IPHorHost, puertoH);
    int clientH_connTrialsCounter = 0;
    while(!clientH.connected())
    {
        Serial.print(".");
        delay(500);
        clientH_connTrialsCounter++;
        if(clientH_connTrialsCounter > 8)
        {
            Serial.println("ClientH not responding");
            break;
        }
    }
    if(clientH_connTrialsCounter <= 8)
    {
        clientHConnected_flag = true;
        digitalWrite(pinSocketHorConn, HIGH);
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

void CommTCP::sendCommand(String host_key, String command)
{
    if(host_key == "H")
    {
        //clientH = serverH->available();
        if(clientH) {
            if (clientH.connected()) {
                #if commVerbose
                    Serial.print(", ClientH Connected.");
                #endif

                #if commActiva
                    //serverH->print(command);
                    clientH.println(command);
                #endif
            }
            else {
            #if commVerbose
                Serial.print(", ClientH NOT connected.");
            #endif
            }
        }
        else {

        }
    }
    else if (host_key == "V") {
        //clientV = serverV->available();
        if(clientV)
        {
            if (clientV.connected()) {
                #if commVerbose
                    Serial.print(", ClientV Connected");
                #endif

                #if commActiva
                    clientV.println(command);
                    //clientV.write(command);
                #endif
            }
            else {
                #if commVerbose
                    Serial.print("ClientV not connected.");
                #endif
            }
        }
        else {
            Serial.print(", !clienteV");
        }
    }
    else
    {
        Serial.println(", Host Key not valid.");
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


