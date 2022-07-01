
win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Grúa_Incorporación/Repositorio_Akoui/Componentes/ModuloControl_Horizontal/Programa/Grua_Horizontal_Arduino_ESP_PIO_Station/ESP-01/include"
INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Grúa_Incorporación/Repositorio_Akoui/Componentes/ModuloControl_Horizontal/Programa/Grua_Horizontal_Arduino_ESP_PIO_Station/ESP-01/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/tools/sdk/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/cores/esp8266"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/tools/sdk/lwip2/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/variants/generic"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ArduinoOTA"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/DNSServer/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/EEPROM"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266AVRISP/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266HTTPClient/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266HTTPUpdateServer/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266LLMNR"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266NetBIOS"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266SSDP"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266SdFat/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266WebServer/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266WiFi/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266WiFiMesh/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266httpUpdate/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/ESP8266mDNS/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/Ethernet/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/GDBStub/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/Hash/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/I2S/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/LittleFS/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/Netdump/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/SD/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/SDFS/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/SPI"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/SPISlave/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/Servo/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/SoftwareSerial/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/TFT_Touch_Shield_V2"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/Ticker/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/Wire"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/esp8266/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/lwIP_PPP/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/lwIP_enc28j60/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/lwIP_w5100/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduinoespressif8266/libraries/lwIP_w5500/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa/xtensa-lx106-elf/include/c++/10.3.0"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa/xtensa-lx106-elf/include/c++/10.3.0/xtensa-lx106-elf"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa/lib/gcc/xtensa-lx106-elf/10.3.0/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa/lib/gcc/xtensa-lx106-elf/10.3.0/include-fixed"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-xtensa/xtensa-lx106-elf/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/tool-unity"

DEFINES += "PLATFORMIO=50203"
DEFINES += "ESP8266"
DEFINES += "ARDUINO_ARCH_ESP8266"
DEFINES += "ARDUINO_ESP8266_ESP01"
DEFINES += "F_CPU=80000000L"
DEFINES += "__ets__"
DEFINES += "ICACHE_FLASH"
DEFINES += "ARDUINO=10805"
DEFINES += "ARDUINO_BOARD=&quot;PLATFORMIO_ESP01&quot;"
DEFINES += "FLASHMODE_QIO"
DEFINES += "LWIP_OPEN_SRC"
DEFINES += "NONOSDK22x_190703=1"
DEFINES += "TCP_MSS=536"
DEFINES += "LWIP_FEATURES=1"
DEFINES += "LWIP_IPV6=0"
DEFINES += "VTABLES_IN_FLASH"
DEFINES += "MMU_IRAM_SIZE=0x8000"
DEFINES += "MMU_ICACHE_SIZE=0x8000"

OTHER_FILES += platformio.ini


CONFIG += c++17

SOURCES += \
    src/ESP_TCP_Comm.cpp
