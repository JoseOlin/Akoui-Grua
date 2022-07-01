#ifndef MOVIMIENTO_HPP
#define MOVIMIENTO_HPP

#include "Config.hpp"

int pinIzquierda = 2;
int pinDerecha = 3;
int pinPwm = 5; // NOTA: En caso de modificar, definir pines que soporten PWM.

char controlValue;
int pwmValue;

void pinsConfig()
{
    /* The pin configuration for MC33296 driver */
      // Configurar GPIO0 y GPIO2
    pinMode(pinIzquierda, OUTPUT);
    pinMode(pinDerecha, OUTPUT);

    #if ACTIVE_ON_HIGH
      digitalWrite(pinIzquierda, LOW);
      digitalWrite(pinDerecha, LOW);
    #else // Active on LOW.
      digitalWrite(pinIzquierda, HIGH); // Activo en BAJO, inactivo en ALTO.
      digitalWrite(pinDerecha, HIGH);
    #endif
}


void akouiControl(controlValue, pwmVaue)
{
    /*
     *
    */

    if(controlValue == 'L' || controlValue == 'R')
    {
        motorControl(controlValue, pwmValue);
    }
    else if (controlValue == 'S')
    {
        // Stop

    }
    else if (controlValue == 'E')
    {
        // Emergency Stop
    }
}

void detener()
{
    analogWrite(pinPwm, 0);
}

void motorControl(controlValue, pwmMaxValue)
{
    // The rest of the code use Active on High Logic for readability, only here in inverted
    // when the Active on High logic is activated.
    int pwmIncrementDelay = 100;
  #if ACTIVE_ON_HIGH

  #else
    // Aplicar lógica de activo en bajo.
    flagMoverIzq = !flagMoverIzq;
    flagMoverDer = !flagMoverDer;
  #endif
    if (controlValue == 'L')
    {
        pinDireccion = pinIzquierda;
    }
    else
    {
        pinDireccion = pinDerecha;
    }

    digitalWrite(pinDireccion, 1);
    int pwm = 0;
    while(pwm < pwmMaxValue)
    {
        analogWrite(pinPwm, pwm);
        pwm += 20;
        delay(pwmIncrementDelay);
    }

}
#endif // MOVIMIENTO_HPP
