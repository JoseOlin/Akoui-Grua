/* Este sketch se programa en el Arduino Nano del módulo de control horizontal de la grúa

* El Arduino recibe valores del ESP-01 y controla el Driver DC del módulo.

*  Placa:

Para mover la grúa hacia la izquierda se recibe el valor LNNN
Donde NNN es un valor PWM entre 1 y 255
Para mover la grúa hacia la derecha RNNN
Para detener la grúa S
Paro de emergencia E
Si no se recibe ningun valor, la grúa se detiene.

 */

#include <Arduino.h>
#include "Comunicacion.hpp"
#include "Movimiento.hpp"


uint8_t flagParoEmerg = 0;

// Dirección actual de la grúa.
uint8_t flagMoverIzq = 0, flagMoverDer = 0;

//int valorLimiteIzq, valorLimiteDer;
//String req, s;


void setup()
{
    commInit();
    pinsConfig();

    delay(10);
}

void loop() 
{  
  //valorLimiteIzq = digitalRead(limiteIzq); // Normalmente HIGH. LOW cuando se activan.
  //valorLimiteDer = digitalRead(limiteDer);

    leerValores(controlValue, pwmValue);

    akouiControl(controlValue, pwmVaue);
    //controlMotor();

    //flagMoverIzq = 0;
    //flagMoverDer = 0;
      
    //contNoClient = 0; // Esta se reinicia cuando haya un nuevo cliente.

    // Verificar Paro de Emergencia
    if (req.indexOf("/paro/0") != -1)
    {
        flag_ParoEmerg = 0;    // Paro de Emergencia Desactivado
        #if DEBUG_MOVIMIENTO
        Serial.println("Paro de Emergencia Desactivado");
        #endif
    }

    if (req.indexOf("/paro/1") != -1){
        flag_ParoEmerg = 1;   // Paro de Emergencia Activado
        #if DEBUG_MOVIMIENTO
        Serial.println("Paro de Emergencia Activado");
        #endif
    }

  // Realizar acción considerando el Paro de Emergencia
  if (!flag_ParoEmerg) // Si el Paro de Emergencia está Desactivado.
  {     
      // En esta sección se aplica lógica de activo en Alto, que es más fácil de revisar; en controlMotor se invierte.   
      
      if (req.indexOf("/izquierda/1") != -1)
      { // Iniciar el movimiento hacia la izquierda.
        /*if(valorLimiteIzq == 1) {*/
          flagMoverIzq = 1;
          flagMoverDer = 0;
          
          #if DEBUG_MOVIMIENTO
          Serial.println("Moviendo izq.");
          #endif
         /*} else {
          flagMoverIzq = 0;   flagMoverDer = 0;
        }*/
      }
      
      else if (req.indexOf("/derecha/1") != -1)
      {
        /*if(valorLimiteDer == 1) {*/  
          flagMoverIzq = 0;
          flagMoverDer = 1; 
          #if DEBUG_MOVIMIENTO
          Serial.println("Moviendo der.");
          #endif
        /*} else { 
          flagMoverIzq = 0;  flagMoverDer = 0;
        }*/
      }
      else if (req.indexOf("/izquierda/0") != -1) // Si aparece la cadena /izquierda/0 al menos una vez.
      { // Detener el movimieto hacia la izquierda.
        flagMoverIzq = 0; 
        flagMoverDer = 0;
        
        #if DEBUG_MOVIMIENTO
        Serial.println("Detener mov. izq.");
        #endif
      }
      else if (req.indexOf("/derecha/0") != -1)
      { // Detener el movimiento hacia la derecha.
        flagMoverIzq = 0;
        flagMoverDer = 0;
        
        #if DEBUG_MOVIMIENTO
        Serial.println("Detener mov. der.");
        #endif
      }
  }
  else // flag_ParoEmergencia = 1: ACTIVADO.
  {
    flagMoverIzq = 0;
    flagMoverDer = 0;
    
    #if DEBUG_MOVIMIENTO
      Serial.println("Paro de Emergencia Activado.");
    #endif

  }

   // Si ambas banderas de dirección están activas, desactivarlas ambas.
    if((flagMoverIzq == 1) && (flagMoverDer == 1))
    {
        flagMoverIzq = 0;
        flagMoverDer = 0;
    }

}
