#ifndef CONFIG_HPP
#define CONFIG_HPP

#define CASA 1
#define DEVMODE 1

#define DEBUG_MOVIMIENTO 1
#define DEBUG_COM 1
#define ACTIVE_ON_HIGH 0 //Logic for the DC driver.


unsigned long stealthMode_delay = 10000;    // ms
unsigned long heartbeat_period = 6000;      // ms
int maxPower = 80;  // %
unsigned int controlPeriod = 50;            // ms
unsigned int messagesPeriod = 300;          // ms

#define BOOT_MESSAGES 1
#endif // CONFIG_HPP
