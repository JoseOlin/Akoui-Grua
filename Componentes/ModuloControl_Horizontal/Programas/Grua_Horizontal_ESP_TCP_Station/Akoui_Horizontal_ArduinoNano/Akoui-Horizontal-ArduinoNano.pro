
win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Grúa_Incorporación/Repositorio_Akoui/Componentes/ModuloControl_Horizontal/Programa/Grua_Horizontal_Arduino_ESP_Station_PIO/include"
INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Grúa_Incorporación/Repositorio_Akoui/Componentes/ModuloControl_Horizontal/Programa/Grua_Horizontal_Arduino_ESP_Station_PIO/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/cores/arduino"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/variants/eightanaloginputs"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/EEPROM/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/HID/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/SPI/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/SoftwareSerial/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/Wire/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/7.3.0/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/7.3.0/include-fixed"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/avr/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/tool-unity"

DEFINES += "PLATFORMIO=50203"
DEFINES += "ARDUINO_AVR_NANO"
DEFINES += "F_CPU=16000000L"
DEFINES += "ARDUINO_ARCH_AVR"
DEFINES += "ARDUINO=10808"
DEFINES += "__AVR_ATmega328P__"



OTHER_FILES += platformio.ini


CONFIG += c++11

SOURCES += \
    src/Grua_Horizontal_Station.cpp

HEADERS += \
    src/Comunicacion.hpp \
    src/Config.hpp \
    src/Movimiento.hpp
