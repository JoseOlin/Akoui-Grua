/* Programa de Arduino Nano del módulo de control horizontal de la grúa Akoui.

* El Arduino recibe valores del ESP-01 y controla el Driver DC del módulo.

*  Placa:

Para mover la grúa hacia la izquierda se recibe el mensaje <l,N>
Donde N es un valor PWM entre 1 y 255

Para mover la grúa hacia la derecha <r,N>
Para detener la grúa <S>
Paro de emergencia <E>
Si no se recibe ningun valor, la grúa se detiene.
 */


#include "Akoui.hpp"

unsigned long lastTime = 0;
unsigned long currentTime = 0;
unsigned long lastMsg_Time = 0;
unsigned long lastHbeat_time = 0;
unsigned long lastStealthMode_time = 0;

unsigned int periodsToMessage;
unsigned int periodsToMessage_Cnt;

//bool enterControlLoop = false;

Akoui akoui;

bool mainInit()
{
    commSerial_Init();

    akoui.init(controlPeriod, maxPower, stealthMode_delay, heartbeat_period);

    if(messagesPeriod >= controlPeriod)
    {
        periodsToMessage = messagesPeriod / controlPeriod;
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
    if(!mainInit())
    {
        Serial.println("Some error ocurred on mainInit()");
    }

#if DEVMODE
    delay(1500);
#endif

    lastTime = millis();
    lastHbeat_time = millis();
    lastStealthMode_time = millis();

    Serial.println("Esperando cliente...");
}


void loop() 
{

    if(!client)
    {
        client = server.available();
        delay(1000);
        Serial.print(".");
    }
    else
    {
        if(client.connected()) {
            Serial.println("Client Connected");
            //digitalWrite(akoui.pinLEDClientConnected, HIGH);
            akoui.clientConnected_flag = true;
            lastHbeat_time = millis();

            lastStealthMode_time = millis();
        }
        else{
            Serial.println("No Client Connected");
            //digitalWrite(akoui.pinLEDClientConnected, LOW);
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
                    Serial.println("Hbeat");
                }
                else if (akoui.msgType != MessageType::Error){
                    lastMsg_Time = millis();
                    lastStealthMode_time = millis();
                    Serial.println("New message");

                    akoui.loopsToStealthMode_counter = 0;
                    akoui.messagePeriodExpired_delivered = false;
                }
                else
                {
                    Serial.println("Error in the message");
                }
            }

            if( (currentTime - lastTime) >= controlPeriod ) // Control synced loop (20 ms).
            {

                if( (currentTime - lastMsg_Time) >= messagesPeriod )
                {
                    // Stop Akoui.
                    akoui.stop(false);
                    if(!akoui.messagePeriodExpired_delivered)
                    {
                        Serial.println("MessagePeriod expired. Stopping.");
                        akoui.messagePeriodExpired_delivered = true;
                    }
                }
                else
                {
                    akoui.startingActions( );
                }

                akoui.stealthModeCheck(lastStealthMode_time, currentTime);

                if(!akoui.hearbeat_check(currentTime, lastHbeat_time))
                {
                    Serial.println("No se recibió el heartbeat");
                    client.stop();
                    akoui.clientConnected_flag = false;
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
        akoui.setConnectionStatusLEDs();
    }

    currentTime = millis();
    akoui.stealthModeCheck(lastStealthMode_time, currentTime);
    akoui.stop(false);
}
