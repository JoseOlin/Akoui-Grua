#include "JoystickShield.h"

JoystickShield::JoystickShield(CommTCP* comm)
{
    configurePins();
    this->comm = comm;
}

void JoystickShield::leerBotones()
{
  // Los botones tienen resistencias pull-up, por lo tanto están activos en Bajo.

  pinBtnSubir_value = digitalRead(pinBtnSubir);
  pinBtnBajar_value = digitalRead(pinBtnBajar);
  pinBtnIzq_value = digitalRead(pinBtnIzq);
  pinBtnDer_value = digitalRead(pinBtnDer);

  pinBtnCerrarPinza_value = digitalRead(pinBtnCerrarPinza);
  pinBtnAbrirPinza_value = digitalRead(pinBtnAbrirPinza);

  pinBtnParo_value = digitalRead(pinBtnParo);

}


void JoystickShield::validarEstadoBoton(int &estado, bool &flagActivo)
{
    if(estado == ACTIVE_STATE && !flagActivo)
    {
        //Pasó de Inactivo a Activo
        flagActivo = true;
    }
    else if(estado == INACTIVE_STATE && flagActivo)
    {
        // Pasó de Activo a Inactivo

        #if commHttpActiva
        String comando_Desactivar = serverName + comando + "0";
        httpRequest(comando_Desactivar);
        delay(delayRequestParada);

        httpRequest(comando_Desactivar);
        delay(delayRequestParada);

        httpRequest(comando_Desactivar);
        #endif
        flagStopVertical = true;
        flagActivo = false;

        //TODO: Probar si es mejor implementar un contador y enviar un Request por ciclo del loop.
    }
}

void JoystickShield::validarEstadoBotones()
{
//#if commHttpActiva // Se valida dentro de las funciones
    validarEstadoBoton(pinBtnSubir_value, flagSubiendo);
    validarEstadoBoton(pinBtnBajar_value, flagBajando);

    validarEstadoBoton(pinBtnIzq_value, flagMoviendoIzq);
    //validarEstadoBoton(pinBtnDer_value, flagMoviendoDer, comm->serverNameH, "/derecha/");
    validarEstadoBoton(pinBtnDer_value, flagMoviendoDer);

    //validarEstadoBoton_Continuo(izquierda, serverNameH, "/izquierda/");
    //validarEstadoBoton_Continuo(derecha, serverNameH, "/derecha/");

    validarBotones_Pinza(pinBtnAbrirPinza_value,  flagAbriendo, "Abrir");
    validarBotones_Pinza(pinBtnCerrarPinza_value, flagCerrando, "Cerrar");


    validarBoton_Paro(pinBtnParo_value, flagParo);
}

void JoystickShield::validarEstadoBoton_Continuo(int &estado,
                                                 const String serverName, String comando)
{
    if(estado == LOW)
    {
        Serial.print("Activando "); Serial.println(comando);
        String comando_Activar = serverName + comando + "1";

        #if commHttpActiva
        //httpRequest(comando_Activar);
        #endif
        #if commTcpActiva

        #endif
    }
    /*else if(estado == HIGH)
    {
        Serial.print("Desactivando "); Serial.println(comando);
        String comando_Desactivar = serverName + comando + "0";
        #if comActiva
        httpRequest(comando_Desactivar);
        #endif
    }*/
}

void JoystickShield::validarBotones_Pinza(int estado, bool &flagActivo, String comando)
{
    if(estado == LOW && !flagActivo)
    {
        Serial.print("Activando "); Serial.println(comando);
        //String comando_Activar = serverName + comando + "1";
        flagActivo = true;
    }
    else if(estado == HIGH && flagActivo)
    {
        Serial.print("Desactivando "); Serial.println(comando);
        //String comando_Activar = serverName + comando + "0";
        flagActivo = false;
    }
}


void JoystickShield::displayButtonsValues()
{
   Serial.print(", bU: "); Serial.print(pinBtnSubir_value);

   Serial.print(", bD: "); Serial.print(pinBtnBajar_value);
   Serial.print(", bL: "); Serial.print(pinBtnIzq_value);
   Serial.print(", bR: "); Serial.print(pinBtnDer_value);

   Serial.print(", bC: "); Serial.print(pinBtnCerrarPinza_value);
   Serial.print(", bO: "); Serial.print(pinBtnAbrirPinza_value);

   Serial.print(", bS: "); Serial.print(pinBtnParo_value);
}

void JoystickShield::validarBoton_Paro(int estado, bool &flagActivo)
{
  // La activación y desactivación del paro es con la misma acción del botón,
  //  así que debe validarse que una vez leído, el
  //  botón no se vuelva a leer durante cierto periodo.

    unsigned long tiempoActual = millis();
    unsigned long tiempoTranscurrido = tiempoActual - tiempoUltimaPulsacionParo;

  if(estado == LOW && flagActivo == false && (tiempoTranscurrido > umbralLecturaParo) )
  {
    Serial.println("Activando paro de emergencia");


    #if commHttpActiva
    String comandoActivarParo_V = serverNameV + "/paro/1";
    String comandoActivarParo_H = serverNameH + "/paro/1";
    httpRequest(comandoActivarParo_V);
    delay(10);
    httpRequest(comandoActivarParo_V);

    httpRequest(comandoActivarParo_H);
    delay(10);
    httpRequest(comandoActivarParo_H);
    #endif


    flagActivo = true;
    tiempoUltimaPulsacionParo = millis();
  }
  else if(estado == LOW && flagActivo == true && tiempoTranscurrido > umbralLecturaParo)
  {
    Serial.println("Desactivando paro de emergencia");
     #if commHttpActiva
    String comandoDesactivarParo_V = serverNameV + "/paro/0";
    String comandoDesactivarParo_H = serverNameH + "/paro/0";
    httpRequest(comandoDesactivarParo_V);
    httpRequest(comandoDesactivarParo_H);
    #endif
    flagActivo = false;
    tiempoUltimaPulsacionParo = millis();
  }
}

void JoystickShield::sendCommands()
{
    if(flagSubiendo)
    {
        Serial.print(", Enviar comandoUp");
        #if commActiva
            #if commTcpActiva
                comm->sendCommand("V", comandoUp);
            #elif commHttpActiva
                const String comando = "/subir/";
                String serverName = comm->serverNameV;
                String comando_Activar = serverName + comando + "1";
                httpRequest(comando_Activar);
            #endif
        #endif
    }
    else if (flagBajando)
    {
        Serial.print(", Enviar comandoDown");
        #if commActiva
            #if commTcpActiva
                comm->sendCommand("V", comandoDown);
            #elif commHttpActiva

            #endif
        #endif
    }
    else if(flagStopVertical)
    {
        Serial.print(", Enviar comandoStop");
        #if commActiva
            #if commTcpActiva
                comm->sendCommand("V", comandoStop);
            #elif commHttpActiva

            #endif
        #endif
        flagStopVertical = false;
    }
    else
    {
        //Serial.print(", Enviar comandoStopVer");
        #if commActiva
            #if commTcpActiva
                //comm->sendCommand(comm->serverName_Ver, comandoStop);
            #elif commHttpActiva

            #endif
        #endif
    }


    if(flagMoviendoIzq)
    {

        Serial.print(", Sending comandoLeft");
        #if commActiva
            #if commTcpActiva
                comm->sendCommand("H", comandoLeft);
            #elif commHttpActiva

            #endif
        #endif
    }
    else if(flagMoviendoDer)
    {
        Serial.print(", Sending comandoRight");
        #if commActiva
            #if commTcpActiva
                comm->sendCommand("H", comandoRight);
            #elif commHttpActiva

            #endif
        #endif
    }
    else
    {

    }
}



void JoystickShield::leerJoystick()
{
    JxVal = analogRead(pinJx);
    JyVal = analogRead(pinJy);

    JxAbsDif = abs(Jx_Centro - JxVal);
    JyAbsDif = abs(Jy_Centro - JyVal);
}

void JoystickShield::diplayJoystickValues()
{

  if(JxAbsDif > umbralLecturaJoystick ||
     JyAbsDif > umbralLecturaJoystick)
  {
    Serial.print("Jx: "); Serial.print(JxVal);
    Serial.print(",\tJy: "); Serial.println(JyVal);
  }
}


void JoystickShield::configurePins()
{
    pinMode(pinBtnSubir, INPUT);
    pinMode(pinBtnBajar, INPUT);
    pinMode(pinBtnIzq, INPUT);
    pinMode(pinBtnDer, INPUT);

    pinMode(pinBtnCerrarPinza, INPUT);
    pinMode(pinBtnAbrirPinza, INPUT);

    pinMode(pinBtnParo, INPUT);
}

