/*
 *
 *  The server will set a GPIO pin depending on the value received over TCP.
 *     will set the GPIO2 low,
 *     will set the GPIO2 high
 *  The IP address of the ESP8266 module, will be printed to Serial when
 *  the module is connected.
 */

#include "Akoui_Vertical.hpp"
Akoui akoui;

unsigned long lastTime = 0;
unsigned long currentTime = 0;
unsigned long lastMsg_Time = 0;

unsigned int controlPeriod = 40;
unsigned int messageExpiredPeriod = 320;
unsigned int periodsToMessage;
unsigned int periodsToMessage_Cnt;

bool mainInit()
{
    if(messageExpiredPeriod >= controlPeriod)
    {
        periodsToMessage = messageExpiredPeriod / controlPeriod;
        Serial.print("periodsToMessage: ");  Serial.println(periodsToMessage);
    }
    else
    {
        Serial.println("ERROR: messagesPeriod must be greater than controlPeriod");
        return false;
    }

    return true;
}

void setup()
{
    commInit();

    akoui.pinsConfig();
    mainInit();

    lastTime = millis();
}

void loop()
{
    client = server.available();
    if(client)
    {
        if(client.connected())
        {
            Serial.println("Client Connected");
        }


        while(client.connected())
        {
            currentTime = millis();

            bool newMsg = readValues(akoui.msgType);

            if(newMsg)
            {
                lastMsg_Time = millis();

                //enterControlLoop = true;

                Serial.print(",New message");
                //akoui.startingActions(msgType, lastMsg_Type);
            }

            if( (currentTime - lastTime) >= controlPeriod ) // Control synced loop (20 ms).
            {

                /*if( (periodsToMessage_Cnt > periodsToMessage)  ) // Messages synced loop (200 ms).
                {

                    periodsToMessage_Cnt = 0;
                }

                periodsToMessage_Cnt++;
        */

                if( (currentTime - lastMsg_Time) >= messageExpiredPeriod )
                {
                    // Stop Akoui.
                    akoui.stop(false);
                    Serial.println("MessagePeriod expired. Stopping.");
                }
                else
                {
                    //akoui.evalContinuingActions();
                    akoui.startingActions();
                }

                lastTime = currentTime;
            }

            if(newMsg)
            {
                akoui.lastMsg_Type = akoui.msgType;
            }
        }

        client.stop();
        Serial.println("Client disconnected");
    }

    akoui.stop(false);
}
