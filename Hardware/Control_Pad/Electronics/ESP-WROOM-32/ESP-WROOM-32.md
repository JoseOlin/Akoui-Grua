# ESP-WROOM-32

https://randomnerdtutorials.com/getting-started-with-esp32/

## Pinout

![ESP32-Pinout](ESP32-Pinout.jpg)

https://circuits4you.com/2018/12/31/esp32-devkit-esp32-wroom-gpio-pinout/

### Arduino Framework
En Arduino el pin corresponde con el GPIO. 

| Etiqueta	| GPIO		| Pin Framework Arduino |
|-----------|------------|--------------|
|D2			|	GPIO2 	|  2 	|
|D4			|	GPIO4 	|  4 	|
|D5			|	GPIO5 	|  5 	|
|D18			|	GPIO18	|  18 	|
|D19			|	GPIO19 	|  19 	|
| ...		|	...		|  ...	|


	pinMode(4, OUTPUT);


### NOTAS:

El **GPIO12** (**D12** en el etiquetado de la tablilla) **no debe estar en alto en el arranque**, pues causa conflicto de escritura en la memoria Flash.

	if(Serial.available() > 0)
	  {
	    char c = Serial.read();
	    
	    if (c == 'o')
	    {
	      Serial.println("Activando subida...");
	      String subir_activar = serverNameV + "/subir/1";
	      httpRequest(subir_activar);
	      
	    }
	    else if(c == 'f')
	    {
	      Serial.println("Desactivando subida...");
	      String subir_desactivar = serverNameV + "/subir/0";
	      httpRequest(subir_desactivar);
	    }
	}

## How to power

https://techexplorations.com/guides/esp32/begin/power/


## PlatformIO Board name
esp32dev

[env:esp_wroom_32]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200

## Hall Effect Sensor

https://randomnerdtutorials.com/esp32-hall-effect-sensor/