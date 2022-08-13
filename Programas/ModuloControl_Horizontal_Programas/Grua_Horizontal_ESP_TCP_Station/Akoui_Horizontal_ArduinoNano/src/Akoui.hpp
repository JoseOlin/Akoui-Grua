#ifndef MOVIMIENTO_HPP
#define MOVIMIENTO_HPP

#include "Comunicacion.hpp"

// Dirección actual de la grúa.
//uint8_t flagMoverIzq = 0, flagMoverDer = 0;

//int valorLimiteIzq, valorLimiteDer;
//String req, s;

enum Direction {
    Negative = 0,
    Stopped = 1,
    Positive = 2
};
uint8_t flagParoEmerg = 0;

class Akoui
{
public:
    // Prototypes:

    MessageType msgType = MessageType::ClearedMessage;
    MessageType lastMsg_Type = MessageType::ClearedMessage;

    void init();
    void pinsConfig();
    void startingActions();
    void evalContinuingActions();

    void moveLeft(unsigned int maxPower);
    void moveRight(unsigned int maxPower);
    void stop(bool emergencyStop);
    void accelerate();
    void deccelarate();


    void control(Direction targetDir, unsigned int maxPower);
    void motorDriver(int power);

    void readLimits();
private:
    // Pines Software Serial Rx=2, Tx=3
    int pinPwm = 5; // NOTA: En caso de modificar, definir pines que soporten PWM.
    int pinIzquierda = 6;
    int pinDerecha = 7;



    bool accelerating = false;
    char messageType_car;

    int maxPower = 100;

    int currentPwm = 0;
    int maxPwm = 0;
    int pwmIncrement = 2;

    unsigned long pwmIncrementDelay = 100;


};

void Akoui::init()
{
    if(maxPower > 100) { maxPower = 100; }
    if(maxPower < 10 ) { maxPower = 10;  }

    maxPwm = maxPower * 2.55;

}

void Akoui::pinsConfig()
{
    /* The pin configuration for MC33296 driver */
      // Configurar GPIO0 y GPIO2
    pinMode(pinIzquierda, OUTPUT);
    pinMode(pinDerecha, OUTPUT);
    pinMode(pinPwm, OUTPUT);

    #if ACTIVE_ON_HIGH
      digitalWrite(pinIzquierda, LOW);
      digitalWrite(pinDerecha, LOW);
    #else // Active on LOW.
      digitalWrite(pinIzquierda, HIGH); // Activo en BAJO, inactivo en ALTO.
      digitalWrite(pinDerecha, HIGH);
    #endif
}

void Akoui::startingActions()
{
    if (msgType == MessageType::MoveLeft && lastMsg_Type == MessageType::MoveLeft)
    {

        control(Direction::Negative, maxPower);
        Serial.println("MoveLeft");

        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::MoveLeft;
    }
    else if( msgType == MessageType::MoveRight && lastMsg_Type == MessageType::MoveRight )
    {
        control(Direction::Positive, maxPower);
        Serial.println("MoveRight");

        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::MoveRight;
    }
    else if( msgType == MessageType::Stop )
    {
        stop(false);
        Serial.println("Stop");
        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::Stop;
    }
    else if( msgType == MessageType::EmergencyStop )
    {
        stop(true);
        Serial.println("Emergency Stop");
        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::EmergencyStop;
    }


    else if( msgType == MessageType::GoLimitL )
    {

    }
    else if( msgType == MessageType::GoLimitR )
    {

    }
    else if( msgType == MessageType::SetConfigData)
    {

    }
    else if( msgType == MessageType::SetMotorPosition)
    {

    }

    else
    {
        Serial.println("No message Stop");
        stop(false);
    }

}

void Akoui::evalContinuingActions()
{
    if (lastMsg_Type == MessageType::MoveLeft )
    {

        control(Direction::Negative, maxPower);

        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::MoveLeft;
    }
    else if( lastMsg_Type == MessageType::MoveRight )
    {
        control(Direction::Positive, maxPower);

        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::MoveRight;
    }
    else if( lastMsg_Type == MessageType::Stop )
    {
        stop(false);

        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::Stop;
    }
    else if( lastMsg_Type == MessageType::EmergencyStop )
    {
        stop(true);

        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::EmergencyStop;
    }
}

void Akoui::accelerate()
{

    if(currentPwm < maxPwm)
    {
        currentPwm += pwmIncrement; // TODO: Add function to calculate increment according to a target acceleration.
    }
    else
    {
        currentPwm = maxPwm;
    }

    analogWrite(pinPwm, currentPwm);
}
void Akoui::deccelarate()
{

    if(currentPwm >= 0)
    {
        currentPwm -= pwmIncrement;
    }
    else
    {
        currentPwm = 0;
    }

    analogWrite(pinPwm, currentPwm);
}

void Akoui::moveLeft(unsigned int maxPower)
{
    digitalWrite(pinIzquierda, HIGH);
    digitalWrite(pinDerecha, LOW);

    //if(maxPower > 100) maxPower = 100; //Done in init()
    //if(maxPower < 0) maxPower = 0;

    //int maxPwm = maxPower * 2.55;

    accelerate();
}
void Akoui::moveRight(unsigned int maxPower)
{
    digitalWrite(pinIzquierda, LOW);
    digitalWrite(pinDerecha, HIGH);

    accelerate();
}
void Akoui::stop(bool emergencyStop)
{
    digitalWrite(pinIzquierda, LOW);
    digitalWrite(pinDerecha, LOW);

    if(emergencyStop)
    {
        analogWrite(pinPwm, 0);
    }
    else
    {
        deccelarate();
    }

}

void Akoui::control(Direction targetDir, unsigned int maxPower)
{
    /*
     *
    */

    if(targetDir == Direction::Negative) // To the origin (bed)
    {
        moveLeft(maxPower);

        //motorControl(controlValue);
    }
    else if (targetDir == Direction::Positive)
    {
        moveRight(maxPower);

    }

    else if (targetDir == Direction::Stopped)
    {
        stop(false);
    }

}

void Akoui::motorDriver(int power)
{
    // The rest of the code use Active on High Logic for readability, only here in inverted
    // when the Active on High logic is activated.
    //int pwmIncrementDelay = 100;
  #if ACTIVE_ON_HIGH

  #else
    // Aplicar lógica de activo en bajo.
    flagMoverIzq = !flagMoverIzq;
    flagMoverDer = !flagMoverDer;
  #endif


    //digitalWrite(pinDireccion, 1);
    /*int pwm = 0;
    while(pwm < pwmMaxValue)
    {
        analogWrite(pinPwm, pwm);
        pwm += 20;
        delay(pwmIncrementDelay);
    }*/

}
void Akoui::readLimits()
{
    //valorLimiteIzq = digitalRead(limiteIzq); // Normalmente HIGH. LOW cuando se activan.
    //valorLimiteDer = digitalRead(limiteDer);
}

#endif // MOVIMIENTO_HPP
