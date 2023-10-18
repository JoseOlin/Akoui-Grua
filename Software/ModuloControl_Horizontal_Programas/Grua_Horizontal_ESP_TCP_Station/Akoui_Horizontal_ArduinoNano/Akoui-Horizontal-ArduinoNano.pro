
win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Grua_Incorporacion/Repositorio_Akoui_Github/Programas/ModuloControl_Horizontal_Programas/Grua_Horizontal_ESP_TCP_Station/Akoui_Horizontal_ArduinoNano/include"
INCLUDEPATH += "/media/Ext4/Proyectos/Autonomia/Grua_Incorporacion/Repositorio_Akoui_Github/Programas/ModuloControl_Horizontal_Programas/Grua_Horizontal_ESP_TCP_Station/Akoui_Horizontal_ArduinoNano/src"
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
    src/Akoui.hpp \
    src/Comunicacion.hpp \
    src/Config.hpp
