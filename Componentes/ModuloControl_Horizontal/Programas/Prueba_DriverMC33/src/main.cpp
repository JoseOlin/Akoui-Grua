#include <Arduino.h>
/* Programa para probar la funcionalidad básica del driver MC33 */

int pinIN1 = 2;
int pinIN2 = 3;

void setup() 
{ 
    pinMode(pinIN1, OUTPUT);
    pinMode(pinIN2, OUTPUT);
}

void loop() { 
    digitalWrite(pinIN1, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(pinIN2, LOW);
    delay(1000);
    
    digitalWrite(pinIN1, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(pinIN2, LOW);
    delay(1000);

    digitalWrite(pinIN1, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(pinIN2, HIGH);
    delay(1000);
    
    digitalWrite(pinIN1, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(pinIN2, LOW);
    delay(1000);
    
 }
