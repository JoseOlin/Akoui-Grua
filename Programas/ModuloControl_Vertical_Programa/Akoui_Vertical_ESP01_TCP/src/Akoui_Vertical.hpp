#ifndef MOVIMIENTO_HPP
#define MOVIMIENTO_HPP

#include "Comunicacion.hpp"

// Dirección actual de la grúa.
//uint8_t flagMoverIzq = 0, flagMoverDer = 0;

//int valorLimiteIzq, valorLimiteDer;
//String req, s;

enum Direction {
    Negative = 0, // Up
    Stopped = 1, //
    Positive = 2 //Downn
};




String req, s;

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

    void moveUp(unsigned int maxPower);
    void moveDown(unsigned int maxPower);
    void stop(bool emergencyStop);
//    void accelerate();
//    void deccelarate();

    void control(Direction targetDir, unsigned int maxPower);
    void motorDriver(int power);

    void readLimits();
private:

    //int pinPwm = 3; // NOTA: En caso de modificar, definir pines que soporten PWM.
    int pinDown = 2;
    int pinUp = 0;
    // Si no se usará comunicación, los pines 1 y 3 pueden usarse como GPIO
    //#define pinParo 1
    //#define pinBlancoNegro 3 // Cuando la grúa se mueve en un sentido, este pin también debe activarse
    // En el programa se activa con ambas direcciones y no afecta, aunque en el diagrama
    // del circuito original sólo se activaba en una dirección.
    // TODO: Revisar la documentación de la grúa para ver la función de este pin.
    uint8_t pinParo = 1;
    uint8_t pinBlancoNegro = 3; // Cuando la grúa se mueve en un sentido, este pin también debe activarse

    uint8_t flagUping, flagDowing;
    uint8_t flagEmergStop = 0;

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
    pinMode(pinUp, OUTPUT);
    pinMode(pinDown, OUTPUT);
    //pinMode(pinPwm, OUTPUT);

    // Los pines del ESP tienen lógica de activo en bajo. (Resistencia pull-up)
    #if ACTIVE_ON_HIGH
      digitalWrite(pinUp, LOW);
      digitalWrite(pinUp, LOW);
    #else // Active on LOW.
      digitalWrite(pinUp, HIGH); // Activo en BAJO, inactivo en ALTO.
      digitalWrite(pinUp, HIGH);
    #endif

    // Configurar GPIO1
    pinMode(pinParo, OUTPUT);
    digitalWrite(pinParo, HIGH); //Inactive in HIGH
    // Configurar GPIO3
    pinMode(pinBlancoNegro, OUTPUT);
    digitalWrite(pinBlancoNegro, HIGH); //Inactive in HIGH
}

void Akoui::startingActions()
{
    if (msgType == MessageType::MoveUp && lastMsg_Type == MessageType::MoveUp)
    {

        control(Direction::Negative, maxPower);
        Serial.println("Move Up");

        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::MoveLeft;
    }

    else if (msgType == MessageType::MoveDown && lastMsg_Type == MessageType::MoveDown)
    {

        control(Direction::Positive, maxPower);
        Serial.println("Move Down");

        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::MoveLeft;
    }

    else if( msgType == MessageType::Stop )
    {
        Serial.println("MsgT::Stop");
        stop(false);
        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::Stop;
    }
    else if( msgType == MessageType::EmergencyStop )
    {
        Serial.println("Emergency Stop");
        stop(true);
        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::EmergencyStop;
    }


    else if (msgType == MessageType::MoveLeft && lastMsg_Type == MessageType::MoveLeft)
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



    else if( msgType == MessageType::GoLimitL )
    {
        //TODO: B. Actions for MessageType::GoLimitL
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

/*
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
*/
void Akoui::moveUp(unsigned int maxPower)
{
#if ACTIVE_ON_HIGH
    digitalWrite(pinDown, LOW);

    digitalWrite(pinUp, HIGH);
    digitalWrite(pinBlancoNegro, HIGH);
#else
    digitalWrite(pinDown, HIGH);

    digitalWrite(pinUp, LOW);
    digitalWrite(pinBlancoNegro, LOW);
#endif

    //accelerate();
}
void Akoui::moveDown(unsigned int maxPower)
{
#if ACTIVE_ON_HIGH
    digitalWrite(pinUp, LOW);

    digitalWrite(pinDown, HIGH);
    digitalWrite(pinBlancoNegro, HIGH);
#else
    digitalWrite(pinUp, HIGH);

    digitalWrite(pinDown, LOW);
    digitalWrite(pinBlancoNegro, LOW);
#endif

    //accelerate();
}
void Akoui::stop(bool emergencyStop)
{
#if ACTIVE_ON_HIGH
    digitalWrite(pinUp, LOW);
    digitalWrite(pinDown, LOW);
    digitalWrite(pinBlancoNegro, LOW);
#else //ACTIVE ON LOW
    digitalWrite(pinUp, HIGH);
    digitalWrite(pinDown, HIGH);

    digitalWrite(pinBlancoNegro, HIGH);
#endif

    /*if(emergencyStop)
    {
        analogWrite(pinPwm, 0);
    }
    else
    {
        deccelarate();
    }*/
}

void Akoui::control(Direction targetDir, unsigned int maxPower)
{
    /*
     *
    */

    if(targetDir == Direction::Negative) // To the origin (bed)
    {
        moveUp(maxPower);
    }
    else if (targetDir == Direction::Positive)
    {
        moveDown(maxPower);
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
    flagUping = !flagUping;
    flagDowing = !flagDowing;
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
