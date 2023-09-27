#ifndef JOYSTICKSHIELD_H
#define JOYSTICKSHIELD_H

#include "CommTCP.h"

/*  Joystick shield buttons mapping
  |        | Shield pin  |  WROOM 32  |
A | Up     |    D2       |   D13       |
B | Left   |    D3       |   D15       |
C | Down   |    D4       |   D14       |
D | Right  |    D3       |   D27       |
*/

/*  Pines comunes WROOM y  NodeMCU v3
 |  WROOM 32 (ESP32)  |   NodeMCU ESP8266) |
 |---------------------|---------------|
 |    D34              |  S3 (GPIO10)  |
 |    D35              |  S2 (GPIO9)   |
 |    D23              |  D0 (GPIO16)  |
 |    D22              |  D1 (GPIO5)   |
 |    D21              |  D4 (GPIO2)  (should not be pulled low at boot)   |
 |    D5               |  D5 ( )        |
 |    TX2 (GPIO17)     |  D6 ( )        |
 |    RX2 (GPIO16)     |  D7 ( )        |
 |    D4               |  D8 (GPIO15) (should not be pulled high at boot)  |

*/

#ifdef ESP8266
    extern int pinBtnA;
    extern int pinBtnB;
    extern int pinBtnC;
    extern int pinBtnD;

    extern int pinBtnE;
    extern int pinBtnF;

    extern int pinJoyX;
    extern int pinJoyY;
    extern int pinJoyPush; // K

    extern int pinDAC1;
    extern int pinDAC2;

    extern int pinLED1;
    extern int pinLED2
    extern int pinLED3;

#else //ESP32

    extern int pinBtnA;
    extern int pinBtnB;
    extern int pinBtnC;
    extern int pinBtnD;

    extern int pinBtnE;
    extern int pinBtnF;

    extern int pinJoyX;
    extern int pinJoyY;
    extern int pinJoyPush; // K

    extern int pinDAC1;
    extern int pinDAC2;

    extern int pinLED1; //Amarillo
    extern int pinLED2; //Azul
    extern int pinLED3; //Verde
#endif


class JoystickShield
{
public:
    JoystickShield();

    int pinLEDWifiConnected;
    int pinLEDClientVConnected; // D5
    int pinLEDClientHConnected; // D18 //Verde

    void pinsDefinition();
    void configurePins();
    //void setCommTCP(CommTCP *comm);

    int pinBtnSubir_value;
    int pinBtnBajar_value;
    int pinBtnIzq_value;
    int pinBtnDer_value;

    int pinBtnCerrarPinza_value;
    int pinBtnAbrirPinza_value;

    int pinBtnParo_value;

    boolean flagStopVertical = false;
    boolean flagStopHorizontal = false;

    void leerBotones();
    void displayButtonsValues();
    void validarEstadoBotones();
    void validarEstadoJoystick();

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

    void turnOffLEDs();
    void setConnectionStatusLEDs();

    void setLoopsToStealthMode(unsigned long loop_delay, unsigned long stealthMode_delay);
    void stealthModeCheck();

    void setLoopsToHeartbeat(unsigned int loop_delay, unsigned int heartbeat_delay);
    void sendHeartbeats();

private:

    /*int pinBtnSubir = pinBtnC;
    int pinBtnBajar = pinBtnA;

    int pinBtnIzq = pinBtnD;
    int pinBtnDer = pinBtnB; */

    //Modificación temporal por falso en el botón de subir.
    int pinBtnSubir;
    int pinBtnBajar;
    int pinBtnIzq;
    int pinBtnDer;

    int pinBtnParo;

    int pinBtnAbrirPinza;
    int pinBtnCerrarPinza;

    int pinJx;
    int pinJy;


    CommTCP* comm;

    boolean flagSubiendo = false, flagBajando = false;
    boolean flagMoviendoIzq = false, flagMoviendoDer = false;
    boolean flagAbriendo = false, flagCerrando = false;
    boolean flagStopButton = false;

    const String comandoUp = "<u>";
    const String comandoDown = "<d>";

    const String comandoLeft = "<l>";
    const String comandoRight = "<r>";

    const String comandoStop = "<S>";
    const String comandoEmergencyStop = "<E>";
    const String comandoHeartbeat = "<H>";

    int JxVal;     int JyVal;
    int JxCentered; int JyCentered;
    int JxCenteredAbs;   int JyCenteredAbs;

    int Jx_Centro = 1850;
    int Jy_Centro = 1870;

    int umbralLecturaJoystick = 250;
    unsigned long umbralLecturaParo = 500; // ms, El botón de paro se leerá cada
    unsigned long tiempoUltimaPulsacionParo = 0;

    unsigned int loopsToStealthMode;
    unsigned int loopsToStealthMode_counter = 0;

    unsigned int loopsToHeartbeat;
    unsigned int loopsToHeartbeat_counter = 0;


    void validarEstadoBoton(int &estado, bool &flagActivo, bool &flagStop);
    void validarEstadoBoton_Continuo(int &estado, const String serverName,
                                     String comando);
    void validarBotones_Pinza(int estado, bool &flagActivo, String comando);
    void validarBoton_Paro(int estado, bool &flagActivo);


};

#endif // JOYSTICKSHIELD_H
