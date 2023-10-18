#ifndef COMUNICACION_HPP
#define COMUNICACION_HPP

#include <Arduino.h>
#include "Config.hpp"

#include <ESP8266WiFi.h>

//#include <SoftwareSerial.h>

#define SerialBaudRate 115200
//#define sSerialBaudRate 19200

//#define sSerialRxPin 10
//#define sSerialTxPin 11

//SoftwareSerial sSerial(sSerialRxPin, sSerialTxPin);

int port = 8888;  //Port number
WiFiServer server(port);

WiFiClient client;

//Server connect to WiFi Network
#if CASA
const char *ssid = "GomezTorres";  // Enter your wifi SSID
const char *password = "lucy1nthesky";  // Enter your wifi Password
#else
const char *ssid = "Telcel-MF253V-5B1F";
const char *password = "258C4Z3dH5";
#endif


const byte numChars = 64;
char receivedChars[numChars];
char parsingBuffer[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;

boolean newData = false;

enum MessageType {
    Error = -1,
    ClearedMessage = 0,

    MoveLeft    = 1,
    MoveRight   = 2,
    MoveUp      = 3,
    MoveDown    = 4,
    Stop        = 5,
    EmergencyStop = 6,

    GoLimitL    = 7,
    GoLimitR    = 8,
    GoLimitUp   = 9,
    GoLimitDown = 10,

    SetConfigData = 11,

    Heartbeat = 12,
};

// MoveLeft,        <l>
// MoveRight,       <r>
// Stop,            <S>
// EmergencyStop    <E>

void recvWithStartEndMarkers();
MessageType parseData();
void showParsedData(char controlValue);


void commSerial_Init()
{
    Serial.begin(SerialBaudRate);
    delay(100);
    Serial.println("Comm init");

}


bool readValues(MessageType &msgType)
{

    recvWithStartEndMarkers();

    if (newData == true)
    {
        strcpy(parsingBuffer, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0

        msgType = parseData();
        //showParsedData(messageType_car);

        newData = false;

        return true;
    }
    return false;
}


void recvWithStartEndMarkers()
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;


    if (client.available() > 0 && newData == false)
    {
        rc = client.read();

        if (recvInProgress == true)
        {
            if (rc != endMarker)
            {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else
            {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
        else if (rc == startMarker)
        {
            recvInProgress = true;
        }
    }


}

//============

MessageType parseData() {      // split the data into its parts
    // Split the data and store it in variables
/*    La cadena que se recibe por serial empieza con alguno de los siguientes caracteres.
    H: Heartbeat
    l: Move Left.
    r: Move right.
    S: Stop.
    E: Emergency Stop.

    L: Move to the Left limit.
    R: Move to the Right limit.
    C: Configuration data.
    M: Movimiento de los motores.
*/
    if(parsingBuffer[0] == 'H')
    {
        return MessageType::Heartbeat;
    }

    else if(parsingBuffer[0] == 'l')
    {
        #if DEBUG_MESSAGE_TYPES
        Serial.println("**MessageType::MoveLeft**");
        #endif
        return MessageType::MoveLeft;
    }

    else if(parsingBuffer[0] == 'r')
    {
        #if DEBUG_MESSAGE_TYPES
        Serial.println("**MessageType::MoveRight**");
        #endif
        return MessageType::MoveRight;
    }

    else if(parsingBuffer[0] == 'S')
    {
        #if DEBUG_MESSAGE_TYPES
        Serial.println("**MessageType::Stop**");
        #endif
        return MessageType::Stop;
    }

    else if(parsingBuffer[0] == 'E')
    {
        #if DEBUG_MESSAGE_TYPES
        Serial.println("**MessageType::EmergencyStop**");
        #endif
        return MessageType::EmergencyStop;
    }


    else if (parsingBuffer[0] == 'L')
    {
        #if DEBUG_MESSAGE_TYPES
        Serial.println("**MessageType::GoLimitL**");
        #endif
        //parseSetSliderPosition();
        return MessageType::GoLimitL;
    }

    else if(parsingBuffer[0] == 'R')
    {
        #if DEBUG_MESSAGE_TYPES
        Serial.println("**MessageType::GoLimitR**");
        #endif
        return MessageType::GoLimitR;
    }

    else if(parsingBuffer[0] == 'C')
    {
        #if DEBUG_MESSAGE_TYPES
        Serial.println("**MessageType::SetConfigData**");
        #endif
        return MessageType::SetConfigData;
    }


    #if DEBUG_MESSAGE_TYPES
    Serial.println("Error: Unexpected character received in parseData()");
    #endif
    return MessageType::Error;
}

//============

void showParsedData(char controlValue)
{
    Serial.print("Control Value ");
    Serial.println(controlValue);
    //Serial.print("Integer ");
    //Serial.println(integerFromPC);
    //Serial.print("Float ");
    //Serial.println(floatFromPC);
}


#endif // COMUNICACION_HPP
