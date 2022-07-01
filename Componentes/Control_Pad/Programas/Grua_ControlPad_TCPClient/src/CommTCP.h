#ifndef COMMTCP_H
#define COMMTCP_H
/* ESP32 boards don’t work with ESP8266WiFi.h,
 * you have to use Wifi.h instead. */

#include <Arduino.h>
#include "Config.h"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif
#include <WiFiClient.h>

class CommTCP
{
public:
    CommTCP();

    String serverNameH = "http://192.168.1.70"; // Dirección del ESP para el movimiento horizontal
    String serverNameV = "http://192.168.1.69"; // Dirección del ESP para el movimiento vertical

    void TCPEcho();
    void sendCommand(String serverS, const String command);


    WiFiServer* serverH = new WiFiServer(puertoH);
    WiFiServer* serverV = new WiFiServer(puertoV);

    WiFiClient clientH;
    WiFiClient clientV;

private:
    const char* ssid = "GomezTorres";
    const char* password = "lucy1nthesky";

    // Start a TCP Server on port
    uint16_t puertoH = 8888;
    uint16_t puertoV = 8889;
};

#endif // COMMTCP_H
