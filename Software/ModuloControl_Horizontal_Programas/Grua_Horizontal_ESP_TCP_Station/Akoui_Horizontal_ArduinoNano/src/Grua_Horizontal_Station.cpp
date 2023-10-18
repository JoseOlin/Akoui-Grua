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

unsigned int controlPeriod = 20;
unsigned int messagesPeriod = 300;
unsigned int periodsToMessage;
unsigned int periodsToMessage_Cnt;

bool enterControlLoop = false;

Akoui akoui;

bool mainInit()
{
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
    commInit();

    akoui.pinsConfig();
    akoui.init();
    mainInit();


    delay(10);
    lastTime = millis();
}

void loop() 
{
    currentTime = millis();

    bool newMsg = readValues(akoui.msgType);

    if(newMsg)
    {
        lastMsg_Time = millis();

        enterControlLoop = true;

        Serial.println("New message");
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

        if( (currentTime - lastMsg_Time) >= messagesPeriod )
        {
            // Stop Akoui.
            akoui.stop(false);
            Serial.println("Stop for messagesPeriod expired");
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
    //controlMotor();

}
