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

    void init(int controlPeriod, int maxPower,
              int stealthMode_delay, unsigned long hbeat_period);
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
    int pinLEDWifiConnected = D2; // Amarillo
    int pinLEDClientConnected = D3; // Verde
    bool wifiConnected_flag = false;
    bool clientConnected_flag = false;

    bool messagePeriodExpired_delivered = false;

    unsigned loopsToStealthMode_counter = 0;

    void setLoopsToStealthMode(unsigned long loop_delay, unsigned long stealthMode_delay);
    //void stealthModeCheck();
    void stealthModeCheck(unsigned long lastStealthModeCheck_time, unsigned long current_time);
    void turnOffLEDs();
    void setConnectionStatusLEDs();
    void wirelessCommInit();
    void setLoopsToHeartbeatCheck(unsigned long loop_delay, unsigned long hearbeat_period);
    bool hearbeat_check(unsigned long currentTime, unsigned long lastHbeat_time);
private:
    // Pines Software Serial Rx=2, Tx=3
    //int pinPwm = 3; // Preferible No usar D3 pues es GPIO0 y debe estar en LOW en el arranque.
    int pinIzquierda = D4;
    int pinDerecha = D5;
    int pinPwm = D7; // NOTA: En caso de modificar, definir pines que soporten PWM.
    int pinStatusFlag = D6;
    int pinFeedback = A0;
    
    // LEDs pins
    // LED Rojo a 3.3V

    bool accelerating = false;
    char messageType_car;

    int maxPower = 100;

    int currentPwm = 0;
    uint16_t accelTime = 600; //ms
    int maxPwm = 0;
    int pwmIncrement = 30;

    //unsigned long pwmIncrementDelay = 20;

    // Stealth Mode (Turn Odd LEDs) Variables
    unsigned int loopsToStealthMode;
    unsigned long stealthModeCheck_period;

    // Heartbeat variables
    unsigned long heartbeat_period;
    //unsigned int loopsToHeartbeat;
};

void Akoui::init(int controlPeriod,
                 int maxPower,
                 int stealthMode_delay,
                 unsigned long heartbeat_period)
{

    pinsConfig();

    wirelessCommInit();

    setLoopsToStealthMode(controlPeriod, stealthMode_delay);

    this->heartbeat_period = heartbeat_period;


    if(maxPower > 100) { maxPower = 100; }
    if(maxPower < 10 ) { maxPower = 10;  }

    maxPwm = maxPower * 2.55;

    pwmIncrement = maxPwm / (accelTime/controlPeriod);
    this->maxPower = maxPower;

    Serial.print("pwmIncrement: "); Serial.println(pwmIncrement);
    Serial.print("maxPower: ");     Serial.println(this->maxPower);
}

void Akoui::pinsConfig()
{
    /* The pin configuration for MC33296 driver */
      // Configurar GPIO0 y GPIO2
    pinMode(pinPwm, OUTPUT);
    pinMode(pinIzquierda, OUTPUT);
    pinMode(pinDerecha, OUTPUT);

    pinMode(pinLEDWifiConnected, OUTPUT);
    pinMode(pinLEDClientConnected, OUTPUT);
    pinMode(pinStatusFlag, INPUT);


    digitalWrite(pinLEDWifiConnected, LOW);
    digitalWrite(pinLEDClientConnected, LOW);
    analogWrite(pinPwm, 0);

    #if ACTIVE_ON_HIGH
      digitalWrite(pinIzquierda, LOW);
      digitalWrite(pinDerecha, LOW);
    #else // Active on LOW.
      digitalWrite(pinIzquierda, HIGH); // Activo en BAJO, inactivo en ALTO.
      digitalWrite(pinDerecha, HIGH);
    #endif
}

void Akoui::wirelessCommInit()
{

    Serial.print("Connecting to SSID ");
#if CASA
    Serial.println("CASA");
#else
    Serial.println("BASE");
#endif

    WiFi.mode(WIFI_STA); // Configurar como Station (Instead of Acces Point)
    WiFi.begin(ssid, password); // Connect to WiFi

    // Wait for connection
    while( WiFi.status() != WL_CONNECTED )
    {
        digitalWrite(pinLEDWifiConnected, HIGH);
        delay(500);
        digitalWrite(pinLEDWifiConnected, LOW);
        Serial.print(".");
    }
    wifiConnected_flag = true;
    digitalWrite(pinLEDWifiConnected, HIGH);

#if BOOT_MESSAGES
    Serial.println("");
    Serial.print("Conectado a ");
    Serial.println(ssid);

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.print(" on port ");
    Serial.println(port);
#endif

    server.begin();

    if(!client)
    {
        Serial.println("!client");
    }
    else{
        Serial.println("client from the very beginning");
    }

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


    else if( msgType == MessageType::GoLimitL )
    {

    }
    else if( msgType == MessageType::GoLimitR )
    {

    }
    else if( msgType == MessageType::SetConfigData)
    {

    }

    else
    {
        Serial.println("No message. Stop");
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
        Serial.print("currentPWm: "); Serial.println(currentPwm);
    }
    else
    {
        currentPwm = maxPwm;
    }


    analogWrite(pinPwm, currentPwm);
}
void Akoui::deccelarate()
{

    if(currentPwm > 0)
    {
        currentPwm -= pwmIncrement;        
        Serial.print("currentPWm: "); Serial.println(currentPwm);
    }
    else
    {
        currentPwm = 0;
    }

    if(currentPwm == 0)
    {
    #if ACTIVE_ON_HIGH
        digitalWrite(pinIzquierda, LOW);
        digitalWrite(pinDerecha, LOW);
    #else
        digitalWrite(pinIzquierda, HIGH);
        digitalWrite(pinDerecha, HIGH);
    #endif
    }

    analogWrite(pinPwm, currentPwm);
}

void Akoui::moveLeft(unsigned int maxPower)
{
#if ACTIVE_ON_HIGH
    digitalWrite(pinIzquierda, HIGH);
    digitalWrite(pinDerecha, LOW);
#else
    digitalWrite(pinIzquierda, LOW);
    digitalWrite(pinDerecha, HIGH);
#endif
    //if(maxPower > 100) maxPower = 100; //Done in init()
    //if(maxPower < 0) maxPower = 0;

    //int maxPwm = maxPower * 2.55;

    accelerate();
}
void Akoui::moveRight(unsigned int maxPower)
{
#if ACTIVE_ON_HIGH
    digitalWrite(pinIzquierda, LOW);
    digitalWrite(pinDerecha, HIGH);
#else
    digitalWrite(pinIzquierda, HIGH);
    digitalWrite(pinDerecha, LOW);
#endif

    accelerate();
}
void Akoui::stop(bool emergencyStop)
{
    if(emergencyStop)
    {
        analogWrite(pinPwm, 0);
        #if ACTIVE_ON_HIGH
            digitalWrite(pinIzquierda, LOW);
            digitalWrite(pinDerecha, LOW);
        #else
            digitalWrite(pinIzquierda, HIGH);
            digitalWrite(pinDerecha, HIGH);
        #endif
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
        Serial.println("MoveLeft");
        //motorControl(controlValue);
    }
    else if (targetDir == Direction::Positive)
    {
        moveRight(maxPower);
        Serial.println("MoveRight");
    }

    else if (targetDir == Direction::Stopped)
    {
        Serial.println("Stop");
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
    //flagMoverIzq = !flagMoverIzq;
    //flagMoverDer = !flagMoverDer;
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


void Akoui::setLoopsToStealthMode(unsigned long loop_delay,
                                  unsigned long stealthMode_delay)
{
    this->stealthModeCheck_period = stealthMode_delay;
    loopsToStealthMode = stealthMode_delay / loop_delay;
    Serial.print("loopsToStealthMode: "); Serial.println(loopsToStealthMode);

}

void Akoui::setLoopsToHeartbeatCheck(unsigned long loop_delay, unsigned long heartbeat_period)
{
    this->heartbeat_period = heartbeat_period;
    //loopsToHeartbeat = this->heartbeat_period / loop_delay;
}

void Akoui::stealthModeCheck(unsigned long lastStealthModeCheck_time,
                             unsigned long current_time)
{
    //if(loopsToStealthMode_counter > loopsToStealthMode)
    if(current_time - lastStealthModeCheck_time >= this->stealthModeCheck_period)
    {
        turnOffLEDs();
    }
    else
    {
        setConnectionStatusLEDs();
        //loopsToStealthMode_counter++;
    }
}

bool Akoui::hearbeat_check(unsigned long currentTime, unsigned long lastHbeat_time)
{
    if(currentTime - lastHbeat_time >= heartbeat_period)
    {
        return false;
    }

    return true;
}


void Akoui::turnOffLEDs()
{
    digitalWrite(pinLEDWifiConnected, LOW);
    digitalWrite(pinLEDClientConnected, LOW);

}
void Akoui::setConnectionStatusLEDs()
{
    digitalWrite(pinLEDWifiConnected, wifiConnected_flag);
    digitalWrite(pinLEDClientConnected, clientConnected_flag);
}

#endif // MOVIMIENTO_HPP
