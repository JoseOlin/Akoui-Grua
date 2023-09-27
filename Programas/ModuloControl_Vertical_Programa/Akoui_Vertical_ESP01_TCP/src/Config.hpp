#ifndef CONFIG_HPP
#define CONFIG_HPP

#define ESP01 0
#define ESPD1MINI 1

#define DEBUG_MOVIMIENTO 1
#define DEBUG_COM 1
#define ACTIVE_ON_HIGH 0
#define AKOUI_VERTICAL 1

// Los pines del módulo de botones tienen lógica de activo en bajo. (Resistencia pull-up)
// El módulo de relevadores tiene lógica de activo en bajo.
// Los pines del ESP D1 Mini

unsigned long heartbeat_period = 5000; // 5s

#define CASA 1
#define BOOT_MESSAGES 1
#endif // CONFIG_HPP
