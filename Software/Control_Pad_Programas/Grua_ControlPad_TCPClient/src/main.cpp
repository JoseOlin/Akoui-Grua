/* Lee los botones y el joystick del Joystick Shield para controlar
 * la grúa.


 Los números de pin corresponden con el número de GPIO en el WROOOM (morados en el pinOut),
que corresponde con la etiqueta en la tablilla (D13 = GPIO13, etc.)

Los pines digitales en el Joystick Shield (no etiquetados) tienen la siguiente configuración
  A
D   B
  C

Su conexión al ESP32 WROOM es la siguiente
 F  E   D  C  B   A
 A: 13
 B: 15
 C: 14
 D: 27
 E: 33
 F: 32

 X: 35
 Y: 34
 K: No conectado, es el botón del joystick.

  Los botones del joystick shield tienen resistencias pull-up, por lo tanto son activos
en bajo.
 El pin 12 no se utilizó como GPIO pues debe estar en LOW en el arranque, y los botones
tienen resistencias pull-up incorporadas.
 Se saltó el 12 y se usó el 15.

 El programa es para un ESP-WROM-32.

 + Placa:  ESP32 Arduino -> ESP32 Dev Module.

  NOTA: (Para usar la tarjeta hay que instalar las librerías manualmente).
Config PlatformIO
lib_deps =
    ESP8266WiFi

*/

#include "JoystickShield.h"

JoystickShield *joyShield;


unsigned int loop_delay = 40; // Evaluar si una frecuencia de lectura
// mayor a la del pad puede mejorar la lectura y evitar pérdida de comandos.
unsigned int heartbeat_delay = 2000; // Periodo para enviar heartbeat a los módulos.
unsigned int stealthMode_delay = 30000; // Delay to Turn off the LEDs



void setup()
{
    Serial.begin(115200);
#if DEVMODE
    delay(500);
#endif
    Serial.println("Comm init.");

    joyShield = new JoystickShield(); // calls configurePins() and assing CommTCP();
    joyShield->setLoopsToStealthMode(loop_delay, stealthMode_delay);
    joyShield->setLoopsToHeartbeat(loop_delay, heartbeat_delay);

    #if commActiva
        Serial.println("La comunicación WiFi está activa, se enviarán comandos a la Grúa.");
    #else
        Serial.println("La comunicación WiFi está inactiva (Modo de Pruebas), NO se enviarán comandos a la Grúa.");
    #endif
#if DEVMODE
    delay(100);
#endif
}

void loop()
{

    joyShield->leerBotones();
    joyShield->leerJoystick();

    joyShield->validarEstadoBotones(); // Given the current logic this should happen after leerJoystick()
    joyShield->validarEstadoJoystick();

    joyShield->diplayJoystickValues();
    joyShield->displayButtonsValues();

    joyShield->sendCommands();

    joyShield->stealthModeCheck();
    joyShield->sendHeartbeats();

    Serial.println("");

    delay(loop_delay);
}




