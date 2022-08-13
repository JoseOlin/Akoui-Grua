#ifndef JOYSTICKSHIELD_H
#define JOYSTICKSHIELD_H

#include "CommTCP.h"

class JoystickShield
{
public:
    JoystickShield(CommTCP* comm);
    int pinBtnSubir_value;
    int pinBtnBajar_value;
    int pinBtnIzq_value;
    int pinBtnDer_value;

    int pinBtnCerrarPinza_value;
    int pinBtnAbrirPinza_value;

    int pinBtnParo_value;

    void configurePins();

    void leerBotones();
    void displayButtonsValues();
    void validarEstadoBotones();

    void leerJoystick();
    void diplayJoystickValues();

    void sendCommands();

#if ACTIVE_ON_HIGH
    uint8_t ACTIVE_STATE = HIGH;
    uint8_t INACTIVE_STATE = LOW;
#else
    uint8_t ACTIVE_STATE = LOW;
    uint8_t INACTIVE_STATE = HIGH;
#endif
    boolean flagStopVertical = false;

private:

    CommTCP* comm;

    boolean flagSubiendo = false, flagBajando = false;

    boolean flagMoviendoIzq = false, flagMoviendoDer = false;
    boolean flagAbriendo = false, flagCerrando = false;

    boolean flagParo = false;

    const String comandoUp = "<u>";
    const String comandoDown = "<d>";

    const String comandoLeft = "<l>";
    const String comandoRight = "<r>";

    const String comandoStop = "<S>";


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
    int JxAbsDif;
    int JyAbsDif;

    int Jx_Centro = 1850;
    int Jy_Centro = 1870;

    int JxVal;
    int JyVal;
    int umbralLecturaJoystick = 250;
    unsigned long umbralLecturaParo = 500; // ms, El botón de paro se leerá cada

    unsigned long tiempoUltimaPulsacionParo = 0;

    void validarEstadoBoton(int &estado, bool &flagActivo);
    void validarEstadoBoton_Continuo(int &estado, const String serverName,
                                     String comando);
    void validarBotones_Pinza(int estado, bool &flagActivo, String comando);
    void validarBoton_Paro(int estado, bool &flagActivo);


};

#endif // JOYSTICKSHIELD_H
