#include "JoystickShield.h"

JoystickShield::JoystickShield()
{
    configurePins();
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


void JoystickShield::validarEstadoBoton(int &estado, bool &flagActivo,
                                        const String serverName, String comando)
{
  if(estado == LOW && !flagActivo)
  {
    #if comVerbose
    Serial.print("Activando "); Serial.println(comando);
    #endif

    String comando_Activar = serverName + comando + "1";
    #if comHttpActiva
    httpRequest(comando_Activar);
    #endif
    flagActivo = true;
  }
  else if(estado == HIGH && flagActivo)
  {
    #if comVerbose
    Serial.print("Desactivando "); Serial.println(comando);
    #endif

    String comando_Desactivar = serverName + comando + "0";

    #if comHttpActiva
    httpRequest(comando_Desactivar);
    delay(delayRequestParada);

    httpRequest(comando_Desactivar);
    delay(delayRequestParada);

    httpRequest(comando_Desactivar);
    #endif

    flagActivo = false;

    //TODO: Probar si es mejor implementar un contador y enviar un Request por ciclo del loop.
  }
}

void JoystickShield::validarEstadoBotones()
{
    validarEstadoBoton(pinBtnSubir_value, flagSubiendo, serverNameV, "/subir/");
    validarEstadoBoton(pinBtnBajar_value, flagBajando, serverNameV, "/bajar/");

    validarEstadoBoton(pinBtnIzq_value, flagMoviendoIzq, serverNameH, "/izquierda/");
    validarEstadoBoton(pinBtnDer_value, flagMoviendoDer, serverNameH, "/derecha/");

    //validarEstadoBoton_Continuo(izquierda, serverNameH, "/izquierda/");
    //validarEstadoBoton_Continuo(derecha, serverNameH, "/derecha/");

    validarBotones_Pinza(pinBtnAbrirPinza_value,  flagAbriendo, "Abrir");
    validarBotones_Pinza(pinBtnCerrarPinza_value, flagCerrando, "Cerrar");


    validarBoton_Paro(pinBtnParo_value, flagParo);
}
void JoystickShield::validarEstadoBoton_Continuo(int &estado,
                                                 const String serverName,
                                                 String comando)
{
  if(estado == LOW)
  {
    Serial.print("Activando "); Serial.println(comando);
    String comando_Activar = serverName + comando + "1";
    #if comHttpActiva
    httpRequest(comando_Activar);
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


void JoystickShield::validarBoton_Paro(int estado, bool &flagActivo)
{
  // La activación y desactivación del paro es con la misma acción del botón, así que debe validarse que una vez leído, el
  // botón no se vuelva a leer durante cierto periodo.
  unsigned long tiempoActual = millis();
  unsigned long tiempoTranscurrido = tiempoActual - tiempoUltimaPulsacionParo;

  if(estado == LOW && flagActivo == false && (tiempoTranscurrido > umbralLecturaParo) )
  {
    String comandoActivarParo_V = serverNameV + "/paro/1";
    String comandoActivarParo_H = serverNameH + "/paro/1";
    Serial.println("Activando paro de emergencia");
     #if comHttpActiva
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
    String comandoDesactivarParo_V = serverNameV + "/paro/0";
    String comandoDesactivarParo_H = serverNameH + "/paro/0";
    Serial.println("Desactivando paro de emergencia");
     #if comHttpActiva
    httpRequest(comandoDesactivarParo_V);
    httpRequest(comandoDesactivarParo_H);
    #endif
    flagActivo = false;
    tiempoUltimaPulsacionParo = millis();
  }
}

void JoystickShield::leerJoystick()
{
  int JxVal = analogRead(pinJx);
  int JyVal = analogRead(pinJy);

  int JxAbsDif = abs(Jx_Centro - JxVal);
  int JyAbsDif = abs(Jy_Centro - JyVal);

  if(JxAbsDif > umbralLecturaJoystick || JyAbsDif > umbralLecturaJoystick)
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

