#ifndef COMUNICACION_HPP
#define COMUNICACION_HPP

#include <Arduino.h>
#include "Config.hpp"

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
    MoveRight   = 2, // Slide and optionally Track.
    Stop        = 3,
    EmergencyStop = 4,

    GoLimitL = 5,
    GoLimitR = 6,
    SetConfigData = 7,
    SetMotorPosition = 8
};

// MoveLeft,        <l>
// MoveRight,       <r>
// Stop,            <S>
// EmergencyStop    <E>

void recvWithStartEndMarkers();
MessageType parseData();
void showParsedData(char controlValue);


void commInit()
{
    Serial.begin(115200);
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

    while (Serial.available() > 0 && newData == false)
    {
        rc = Serial.read();

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
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

MessageType parseData() {      // split the data into its parts
    // Split the data and store it in variables
/*    La cadena que se recibe por serial empieza con alguno de los siguientes caracteres.
    l: Move Left.
    r: Move right.
    L: Move to the Left limit.
    R: Move to the Right limit.
    C: Configuration data.
    M: Movimiento de los motores.
*/
    if(parsingBuffer[0] == 'l')
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
        // parseConfigData();

        return MessageType::SetConfigData;
    }

    else if(parsingBuffer[0] == 'M')
    {
        #if DEBUG_MESSAGE_TYPES
        Serial.println("**MessageType::SetMotorPosition**");
        #endif

        //parseDataMotor(nMotor_temp, accel_temp, speed_temp, targetPos_temp);

        return MessageType::SetMotorPosition;
    }

    #if DEBUG_MESSAGE_TYPES
    Serial.println("Error: Unexpected character received in parseData()");
    #endif
    return MessageType::Error;
}

//============

void showParsedData(char controlValue) {
    Serial.print("Control Value ");
    Serial.println(controlValue);
    //Serial.print("Integer ");
    //Serial.println(integerFromPC);
    //Serial.print("Float ");
    //Serial.println(floatFromPC);
}


#endif // COMUNICACION_HPP
