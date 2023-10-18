#ifndef JOYSTICKSHIELD_H
#define JOYSTICKSHIELD_H

#include <Arduino.h>

class JoystickShield
{
public:
    JoystickShield();
    int pinBtnSubir_value;
    int pinBtnBajar_value;
    int pinBtnIzq_value;
    int pinBtnDer_value;

    int pinBtnCerrarPinza_value;
    int pinBtnAbrirPinza_value;

    int pinBtnParo_value;

    void configurePins();
    void leerBotones();
    void validarEstadoBotones();
    void leerJoystick();

private:
    String serverNameV = "http://192.168.1.69"; // Dirección del ESP para el movimiento vertical
    String serverNameH = "http://192.168.1.70"; // Dirección del ESP para el movimiento horizontal


    boolean flagSubiendo = false, flagBajando = false;
    boolean flagMoviendoIzq = false, flagMoviendoDer = false;
    boolean flagAbriendo = false, flagCerrando = false;
    boolean flagParo = false;


    int pinBtnSubir = 13; //C
    int pinBtnBajar = 14; //A

    int pinBtnIzq = 27; //D
    int pinBtnDer = 15;  //B

    int pinBtnParo = 16; // K

    int pinDAC1 = 25;
    int pinDAC2 = 26;

    int pinBtnAbrirPinza = 32; //
    int pinBtnCerrarPinza = 33; //

    int pinJx = 35;
    int pinJy = 34;

    int Jx_Centro = 1850;
    int Jy_Centro = 1870;

    int umbralLecturaJoystick = 250;
    unsigned long umbralLecturaParo =  1000; // El botón de paro se leerá cada 1000 ms.

    unsigned long tiempoUltimaPulsacionParo = 0;

    void validarEstadoBoton(int &estado, bool &flagActivo,
                            const String serverName, String comando);
    void validarEstadoBoton_Continuo(int &estado, const String serverName,
                                     String comando);
    void validarBotones_Pinza(int estado, bool &flagActivo, String comando);
    void validarBoton_Paro(int estado, bool &flagActivo);


};

#endif // JOYSTICKSHIELD_H
