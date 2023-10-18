#ifndef CONFIG_H
#define CONFIG_H

#define commActiva 1  // Activa o desactiva la comunicación Wifi.
// Es útil desactivarla para que durante debugueo o prueba de los botones no se
// envíen comandos de movimiento.

// Only one of these two should be active.
#define commTcpActiva 1 // New protocol
#define commHttpActiva 0 // Former protocol

#define commVerbose 1 // Enable INFO messages over UART.
#define DEVMODE 1 // Slow down the setup routine to allow check some values.

#define ACTIVE_ON_HIGH 0 // Define si los botones están Activos en Alto (1) o Activos en Bajo (0)
// El shield tiene resistores pull-up, así que son Activos en Bajo.

#define CASA 1 // 1 para conectarse a la red de casa, 0 para conectarse a la red del dojo.

#endif // CONFIG_H
