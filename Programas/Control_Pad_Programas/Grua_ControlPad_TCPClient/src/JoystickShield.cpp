#include "JoystickShield.h"

JoystickShield::JoystickShield()
{
    configurePins();

    comm = new CommTCP(pinLEDWifiConnected,
                       pinLEDClientVConnected,
                       pinLEDClientHConnected);

}

void JoystickShield::pinsDefinition()
{
#ifdef ESP8266
    pinBtnA = 16;
    pinBtnB = 5;
    pinBtnC = 14;
    pinBtnD = 27;

    pinBtnE = 32;
    pinBtnF = 33;

    pinJoyX = 9;
    pinJoyY = 10;

    pinLED1 = 19;
    pinLED2 = 5;
    pinLED3 = 18;

#else //ESP32
    int pinBtnA = 13; //D13
    int pinBtnB = 15; //D15
    int pinBtnC = 14; //D14
    int pinBtnD = 27; //D27

    int pinBtnE = 32; //D32
    int pinBtnF = 33; //D3

    int pinJoyX = 35;
    int pinJoyY = 34;
    int pinJoyPush = 16; // K

    int pinDAC1 = 25;
    int pinDAC2 = 26;

    int pinLED1 = 19; //Amarillo
    int pinLED2 = 5; //Azul
    int pinLED3 = 18; //Verde

    pinLEDWifiConnected     = pinLED1;
    pinLEDClientVConnected  = pinLED2; // D5
    pinLEDClientHConnected  = pinLED3; // D18 //Verde


    pinBtnSubir = pinBtnB;
    pinBtnBajar = pinBtnA;
    pinBtnIzq = pinBtnD;
    pinBtnDer = pinBtnC;

    pinBtnParo = pinJoyPush; // K

    pinBtnAbrirPinza = pinBtnF; //
    pinBtnCerrarPinza = pinBtnE; //

    pinJx = pinJoyX;
    pinJy = pinJoyY;
#endif
}

void JoystickShield::configurePins()
{
    pinsDefinition();

    pinMode(pinBtnSubir, INPUT);
    pinMode(pinBtnBajar, INPUT);
    pinMode(pinBtnIzq, INPUT);
    pinMode(pinBtnDer, INPUT);

    pinMode(pinBtnCerrarPinza, INPUT);
    pinMode(pinBtnAbrirPinza, INPUT);

    pinMode(pinBtnParo, INPUT);

    pinMode(pinLEDWifiConnected, OUTPUT);
    digitalWrite(pinLEDWifiConnected, LOW);

    pinMode(pinLEDClientVConnected, OUTPUT);
    digitalWrite(pinLEDClientVConnected, LOW);

    pinMode(pinLEDClientHConnected, OUTPUT);
    digitalWrite(pinLEDClientVConnected, LOW);
}



void JoystickShield::setLoopsToStealthMode(unsigned long loop_delay, unsigned long stealthMode_delay)
{
    loopsToStealthMode = stealthMode_delay / loop_delay;
    Serial.print("loopsToStealthMode: "); Serial.println(loopsToStealthMode);

}
void JoystickShield::setLoopsToHeartbeat(unsigned int loop_delay, unsigned int heartbeat_delay)
{
    if(heartbeat_delay > loop_delay)
    {
        loopsToHeartbeat = heartbeat_delay / loop_delay;
        Serial.print("loopsToHeartbeat: "); Serial.println(loopsToHeartbeat);
    }
    else
    {
        Serial.println("ERROR: loop_delay > heartbeat_delay!!! ");
    }
}

void JoystickShield::stealthModeCheck()
{
    if(loopsToStealthMode_counter > loopsToStealthMode)
    {
        turnOffLEDs();
    }
    else
    {
        setConnectionStatusLEDs();
        loopsToStealthMode_counter++;
    }
}
void JoystickShield::sendHeartbeats()
{
    if(loopsToHeartbeat_counter > loopsToHeartbeat)
    {
        comm->sendCommand("V", comandoHeartbeat);
        comm->sendCommand("H", comandoHeartbeat);
        loopsToHeartbeat_counter = 0;
    }

    loopsToHeartbeat_counter++;
}

void JoystickShield::turnOffLEDs()
{
    digitalWrite(pinLEDWifiConnected, LOW);
    digitalWrite(pinLEDClientHConnected, LOW);
    digitalWrite(pinLEDClientVConnected, LOW);

}
void JoystickShield::setConnectionStatusLEDs()
{
    digitalWrite(pinLEDWifiConnected, comm->wifiConnected_flag);
    digitalWrite(pinLEDClientHConnected, comm->clientHConnected_flag);
    digitalWrite(pinLEDClientVConnected, comm->clientVConnected_flag);
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





void JoystickShield::validarEstadoBoton(int &estado, bool &flagActivo, bool& flagStop)
{
    if(estado == ACTIVE_STATE && !flagActivo)
    {
        //Pasó de Inactivo a Activo
        flagActivo = true;
        loopsToStealthMode_counter = 0;

    }
    else if(estado == INACTIVE_STATE && flagActivo)
    {
        // Pasó de Activo a Inactivo
        flagStop = true;
        flagActivo = false;
    }
}

void JoystickShield::validarEstadoJoystick()
{
    if(JxCenteredAbs > umbralLecturaJoystick)
    {
        if(JxCentered < 0)
        {
            // Move left
            pinBtnIzq_value = ACTIVE_STATE;
            pinBtnDer_value = INACTIVE_STATE;

            //validarEstadoBoton(pinBtnIzq_value, flagMoviendoIzq, flagStopHorizontal);
        }
        else
        {
            // Move right
            pinBtnIzq_value = INACTIVE_STATE;
            pinBtnDer_value = ACTIVE_STATE;

            //validarEstadoBoton(pinBtnDer_value, flagMoviendoDer, flagStopHorizontal);
        }
    }
    else
    {
        pinBtnIzq_value = INACTIVE_STATE;
        pinBtnDer_value = INACTIVE_STATE;
        //flagMoviendoIzq = false;
        //flagMoviendoDer = false;
        //flagStopHorizontal = true;

    }

    validarEstadoBoton(pinBtnIzq_value, flagMoviendoIzq, flagStopHorizontal);
    validarEstadoBoton(pinBtnDer_value, flagMoviendoDer, flagStopHorizontal);
}

void JoystickShield::validarEstadoBotones()
{
    /// Vertical movement validation
    if(pinBtnSubir_value == ACTIVE_STATE && pinBtnBajar_value == ACTIVE_STATE)
    { // If opposite buttons are simultaneosly pressed, ignore both and stop.
        flagSubiendo = false;
        flagBajando = false;
        flagStopVertical = true;
    }
    else {
        validarEstadoBoton(pinBtnSubir_value, flagSubiendo, flagStopVertical);
        validarEstadoBoton(pinBtnBajar_value, flagBajando, flagStopVertical);
    }


    /// Horizontal movement validation
    /*if(pinBtnIzq_value == ACTIVE_STATE && pinBtnDer_value == ACTIVE_STATE)
    {
        flagMoviendoIzq = false;
        flagMoviendoDer = false;
        flagStopHorizontal = true;
    }
    else{
        validarEstadoBoton(pinBtnIzq_value, flagMoviendoIzq, flagStopHorizontal);
        validarEstadoBoton(pinBtnDer_value, flagMoviendoDer, flagStopHorizontal);
    }*/


    /// Gripper validation
    //validarEstadoBoton_Continuo(izquierda, serverNameH, "/izquierda/");
    //validarEstadoBoton_Continuo(derecha, serverNameH, "/derecha/");
    if(pinBtnAbrirPinza_value == ACTIVE_STATE && pinBtnCerrarPinza_value == ACTIVE_STATE)
    {
        flagAbriendo = false;
        flagCerrando = false;
    }
    else {
        validarBotones_Pinza(pinBtnAbrirPinza_value,  flagAbriendo, "Abrir");
        validarBotones_Pinza(pinBtnCerrarPinza_value, flagCerrando, "Cerrar");
    }


    validarBoton_Paro(pinBtnParo_value, flagStopButton);
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

void JoystickShield::validarBotones_Pinza(int estado, bool &flagActivo, String action)
{
    if(estado == ACTIVE_STATE && !flagActivo)
    {
        Serial.print("Activando "); Serial.println(action);
        flagActivo = true;
        loopsToStealthMode_counter = 0;
    }
    else if(estado == INACTIVE_STATE && flagActivo)
    {
        Serial.print("Desactivando "); Serial.println(action);
        flagActivo = false;
    }
}

void JoystickShield::displayButtonsValues()
{
   Serial.print(", bU: "); Serial.print(pinBtnSubir_value);
   Serial.print(", bD: "); Serial.print(pinBtnBajar_value);

   Serial.print(",\tbL: "); Serial.print(pinBtnIzq_value);
   Serial.print(", bR: "); Serial.print(pinBtnDer_value);

   Serial.print(",\tbC: "); Serial.print(pinBtnCerrarPinza_value);
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


void JoystickShield::leerJoystick()
{
    JxVal = analogRead(pinJx);
    JyVal = analogRead(pinJy);

    JxCentered = Jx_Centro - JxVal;
    JyCentered = Jy_Centro - JyVal;

    JxCenteredAbs = abs(JxCentered);
    JyCenteredAbs = abs(Jy_Centro - JyVal);
}

void JoystickShield::diplayJoystickValues()
{

  if(JxCenteredAbs > umbralLecturaJoystick ||
     JyCenteredAbs > umbralLecturaJoystick)
  {
    Serial.print(", Jx: "); Serial.print(JxCentered);
    Serial.print(",\tJy: "); Serial.println(JyCentered);
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
            #endif
        #endif
    }
    else if (flagBajando)
    {
        Serial.print(", Enviar comandoDown");
        #if commActiva
            #if commTcpActiva
                comm->sendCommand("V", comandoDown);
            #endif
        #endif
    }
    else if(flagStopVertical)
    {
        Serial.print(", Enviar comandoStop Vert");
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
    else if(flagStopHorizontal)
    {
        Serial.print(", Enviar comandoStop Horz");
        #if commActiva
            #if commTcpActiva
                comm->sendCommand("H", comandoStop);
            #elif commHttpActiva

            #endif
        #endif
        flagStopHorizontal = false;
    }
}



