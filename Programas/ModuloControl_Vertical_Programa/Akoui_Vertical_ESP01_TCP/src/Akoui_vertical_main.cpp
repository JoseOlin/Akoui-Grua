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
unsigned long lastHbeat_time = 0;

unsigned int controlPeriod = 50;
unsigned int messageExpiredPeriod = 300;

unsigned int periodsToMessage;
unsigned int periodsToMessage_Cnt;

bool mainInit()
{
    commInit();

    akoui.init(controlPeriod, heartbeat_period);  // Si el akoui.init se pone antes del commInit tarda más con el falso positivo en la grúa.

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

    mainInit();

    lastTime = millis();
}

void loop()
{
    if(!client)
    {
        client = server.available();
        delay(500);
        //Serial.print(".");
    }
    else
    {
        if(client.connected())
        {
            Serial.println("Client Connected");
            akoui.clientConnected_flag = true;
            lastHbeat_time = millis();
        }
        else{
            //Serial.println("No Client Connected");
            akoui.clientConnected_flag = false;
        }


        while(client.connected())
        {
            currentTime = millis();

            bool newMsg = readValues(akoui.msgType);

            if(newMsg)
            {
                if(akoui.msgType == MessageType::Heartbeat)
                {
                    lastHbeat_time = millis();
                    //Serial.println("Hbeat");
                }
                else {
                    lastMsg_Time = millis();
                    //Serial.println("New message");
                }

                akoui.messagePeriodExpired_delivered = false;
            }

            if( (currentTime - lastTime) >= controlPeriod ) // Control synced loop (20 ms).
            {
                if( (currentTime - lastMsg_Time) >= messageExpiredPeriod )
                {
                    // Stop Akoui.
                    akoui.stop(false);
                    client.flush(); // Probar si el flush permite validar desconexión. Nop.
                    if(!akoui.messagePeriodExpired_delivered)
                    {
                        //Serial.println("MessagePeriod expired. Stopping.");
                        akoui.messagePeriodExpired_delivered = true;
                    }
                }
                else
                {
                    akoui.startingActions();
                }

                //setConnectionStatusLEDs();

                if(!akoui.hearbeat_check(currentTime, lastHbeat_time))
                {
                    //Serial.println("No se recibió el heartbeat");
                    client.stop();
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
        //digitalWrite(akoui.pinLEDClientConnected, LOW);
    }

    akoui.stop(false);
}
