#ifndef COMMTCP_H
#define COMMTCP_H
/* ESP32 boards don’t work with ESP8266WiFi.h,
 * you have to use Wifi.h instead. */

#include <Arduino.h>
#include "Config.h"


#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <WiFiClient.h>


class CommTCP
{
public:
    CommTCP();

    #if commHttpActiva
        String serverNameH = "http://192.168.1.70"; // Dirección del ESP para el movimiento horizontal
        String serverNameV = "http://192.168.1.69"; // Dirección del ESP para el movimiento vertical
    #elif commTcpActiva

        #if CASA
            //String serverName_Ver = "192.168.1.69";
            //IPAddress IP_Ver;// (192,168, 1, 69);

            //String serverName_Hor = "192.168.1.70";
            //IPAddress IP_Hor; //(192, 168, 1, 70);

            const char *IPVerHost = "192.168.1.69";
            const char *IPHorHost = "192.168.1.70";
        #else
            const char *IPHorHost = "192.168.8.48";
        #endif
    #endif


    //void TCPEcho();
    void sendCommand(String serverS, const String command);

    //WiFiServer* serverH;
    //WiFiServer* serverV;

    WiFiClient clientH;
    WiFiClient clientV;

private:

    #if CASA
        const char* ssid = "GomezTorres";
        const char* password = "lucy1nthesky";
    #else
        const char *ssid = "Telcel-MF253V-5B1F";
        const char *password = "258C4Z3dH5";
    #endif

    // Start a TCP Server on port
    uint16_t puertoH = 8888;
    uint16_t puertoV = 8888;

};

#endif // COMMTCP_H
