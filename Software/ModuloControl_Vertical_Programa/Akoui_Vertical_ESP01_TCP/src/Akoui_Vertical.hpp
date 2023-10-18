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

    void init(int controlPeriod, unsigned long heartbeat_period);
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
    bool hearbeat_check(unsigned long currentTime, unsigned long lastHbeat_time);

    MessageType msgType = MessageType::ClearedMessage;
    MessageType lastMsg_Type = MessageType::ClearedMessage;

    bool wifiConnected_flag = false;
    bool clientConnected_flag = false;
    bool messagePeriodExpired_delivered = false;
private:

    //int pinPwm = 3; // NOTA: En caso de modificar, definir pines que soporten PWM.
    // IN1 = D0  //Up o down
    // IN2 = D6 // Cable blanco negro (Se activa junto con el movimiento en cualquier dirección).
    // IN3 = D5 // Up o down
    // IN4 = D7     // Paro emergencia
#if ESP01
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
#elif ESPD1MINI

    // Para bajar activar Relevador 1 y 3
    // Para subir activar Relevador 2 y 3
    //Considerar que con la grúa configurada con el cable en U
    //las direcciones quedan invertidas

    int pinUp = D0;             // Controla Relevador 1
    int pinDown = D5;           // Controla Relevador 2
    uint8_t pinBlancoNegro = D6; //Controla Relevador 3
    uint8_t pinParo = D7;       // Controla Relevador 4
#endif


    uint8_t flagUping, flagDowing;
    uint8_t flagEmergStop = 0;

    bool accelerating = false;
    char messageType_car;

    int maxPower = 100;

    int currentPwm = 0;
    int maxPwm = 0;
    int pwmIncrement = 2;

    unsigned long pwmIncrementDelay = 100;

    // Heartbeat variables
    unsigned long heartbeat_period;
};

void Akoui::init(int controlPeriod,
                 unsigned long heartbeat_period)
{
    pinsConfig();

    this->heartbeat_period = heartbeat_period;

    if(maxPower > 100) { maxPower = 100; }
    if(maxPower < 10 ) { maxPower = 10;  }

    maxPwm = maxPower * 2.55;

}

void Akoui::pinsConfig()
{
    // Configurar GPIO0 y GPIO2
    pinMode(pinUp, OUTPUT);
    pinMode(pinDown, OUTPUT);
    pinMode(pinParo, OUTPUT);
    pinMode(pinBlancoNegro, OUTPUT);
    //pinMode(pinPwm, OUTPUT);


    #if ACTIVE_ON_HIGH
      digitalWrite(pinUp, LOW);
      digitalWrite(pinUp, LOW);
      digitalWrite(pinParo, LOW);
      digitalWrite(pinBlancoNegro, LOW);
    #else // Active on LOW.
      digitalWrite(pinUp, HIGH); // Activo en BAJO, inactivo en ALTO.
      digitalWrite(pinUp, HIGH);
      digitalWrite(pinParo, HIGH); //Inactive in HIGH
      digitalWrite(pinBlancoNegro, HIGH); //Inactive in HIGH
    #endif

}

void Akoui::startingActions()
{

    if (msgType == MessageType::MoveUp && lastMsg_Type == MessageType::MoveUp)
    {
        control(Direction::Positive, maxPower);
#if DEBUG_MOVIMIENTO
        Serial.println("Move Up");
#endif

        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::MoveLeft;
    }

    else if (msgType == MessageType::MoveDown && lastMsg_Type == MessageType::MoveDown)
    {
        control(Direction::Negative, maxPower);
#if DEBUG_MOVIMIENTO
        Serial.println("Move Down");
#endif

        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::MoveLeft;
    }

    else if( msgType == MessageType::Stop )
    {
#if DEBUG_MOVIMIENTO
        Serial.println("MsgT::Stop");
#endif
        stop(false);
        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::Stop;
    }
    else if( msgType == MessageType::EmergencyStop )
    {
#if DEBUG_MOVIMIENTO
        Serial.println("Emergency Stop");
#endif
        stop(true);
        //msgType = MessageType::ClearedMessage;
        //lastMsgType = MessageType::EmergencyStop;
    }

/*
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
*/


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
#else //Active on LOW
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
        moveDown(maxPower);
    }
    else if (targetDir == Direction::Positive)
    {
        moveUp(maxPower);
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

bool Akoui::hearbeat_check(unsigned long currentTime, unsigned long lastHbeat_time)
{
    if(currentTime - lastHbeat_time >= heartbeat_period)
    {
        return false;
    }

    return true;
}
#endif // MOVIMIENTO_HPP
