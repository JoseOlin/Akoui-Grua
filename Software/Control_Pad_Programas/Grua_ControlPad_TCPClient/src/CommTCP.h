#ifndef COMMTCP_H
#define COMMTCP_H

#include <Arduino.h>
#include "Config.h"


/* ESP32 boards don’t work with ESP8266WiFi.h,
 * you have to use Wifi.h instead. */
#ifdef ESP8266
    #include <ESP8266WiFi.h>
#else //ESP32
    #include <WiFi.h>
#endif

#include <WiFiClient.h>


class CommTCP
{
public:
    CommTCP(int pinWifiConn, int pinSocketVerConn, int pinSocketHorConn);

#if commHttpActiva
    #if CASA
        String serverNameH = "http://192.168.1.71"; // Dirección del ESP para el movimiento horizontal
        String serverNameV = "http://192.168.1.72"; // Dirección del ESP para el movimiento vertical
    #else
        String serverNameH = "http://192.168.1.111"; // Dirección del ESP para el movimiento horizontal
        String serverNameV = "http://192.168.1.112"; // Dirección del ESP para el movimiento vertical
    #endif
#elif commTcpActiva

    #if CASA
        const char *IPHorHost = "192.168.1.71";
        const char *IPVerHost = "192.168.1.72";
    #else
        const char *IPHorHost = "192.168.1.111";
        const char *IPVerHost = "192.168.1.112";
    #endif
#endif

    //void TCPEcho();
    void sendCommand(String serverS, const String command);

    //WiFiServer* serverH;
    //WiFiServer* serverV;
    bool wifiConnected_flag = false;
    bool clientHConnected_flag = false;
    bool clientVConnected_flag = false;

    WiFiClient clientH;
    WiFiClient clientV;

private:

    #if CASA
        const char* ssid = "SSID1";
        const char* password = "";
    #else
        const char *ssid = "SSID2";
        const char *password = "";
    #endif

    // Start a TCP Server on port
    uint16_t puertoH = 8888;
    uint16_t puertoV = 8888;

};

#endif // COMMTCP_H











