# MC33926
[Dual MC33926 Motor Driver Carrier](https://www.pololu.com/product/1213)

This dual brushed DC motor driver, based on Freescale’s MC33926 full H-bridge, has a wide operating range of 5 V to 28 V and can deliver almost 3 A continuously (5 A peak) to each of its two motor channels. The MC33926 works with 3 V to 5 V logic levels, supports ultrasonic (up to 20 kHz) PWM, and features current feedback, under-voltage protection, over-current protection, and over-temperature protection.

![0J1889.350](0J1889.350.jpg)

## Conexión rápida
### Para usar como control On/Off

- **IN1 e IN2** controlan la dirección.
- **EN**  puenteado a **HIGH**, cuando está en bajo pone los drivers en modo de bajo consumo.
- **D1 puenteado a GND**
- **D2 puenteado a HIGH**.
- **VDD** debe ser alimentado con 3 a 5V  del microcontrolador.

### Para usar con PWM

- IN1 e IN2 controlan la dirección
- D2 recibe la señal de PWM
- **D1 debe estar a tierra para que no interfiera con D2** (ya que este pin también puede recibir PWM pero es más usual ponerlo en D2).
- **EN** puenteado a HIGH (Está por defecto en bajo, poniendo el puente en modo de bajo consumo).
- VDD conectado al voltaje del microcontrolador

### Otros pines útiles
**INV**: Si está puenteado invierte el comportamiento de IN1 e IN2.

**SF**: Status flag. Normalmente alta. Pasará  a bajo si hay sobrecorriente (corto) o sobretemperatura. También pasa a bajo cuando D1 o D2 deshabilitan las entradas. Está debilmente conectada a HIGH así que no puede conectarse un LED, sólo puede leerse desde un microcontrolador.

**FB**: 525 mV por amper. Para estimar la corriente consumida.



## Basic Application Connections
In a typical application, **five I/O lines are used** to connect each motor driver channel to a microcontroller: the two input lines, IN1 and IN2, for direction control, one of the disable lines, D1 or D2, for PWM speed control, the current sense output, FB, for monitoring motor current draw (connected to an analog-to-digital converter input) and the status flag, SF, for monitoring motor driver errors. 

The **control lines can be reduced to two pins per channel** if PWM signals are applied directly to the two input pins with both disable pins held inactive. In each of these cases, the other unused lines must be set to enable proper operation. For example, if D2 is used for the PWM input (as is typically the case), D1 must be held low to prevent it from disabling the motor driver. The circuit board provides convenient jumper points for overriding the motor driver defaults without having to connect extra wires to the module.

The current sense and status flag connections are optional, though monitoring of the status flags can allow detection of latched fault conditions. The status flags are open-drain output, so the two status flag can be wired together for applications where I/O pins are scarce and determining which motor driver is experiencing a fault condition is not necessary.

Note that the default state of the enable pin, EN, is LOW, which holds both motor driver chips in a low-current sleep mode. You will need to hold this pin high (either with an external connection or via the default-overriding jumper next to the pin) to allow the board to run.

## Pinout detallado
![](./0J1889.1200.jpg) 

The default states of many of the MC33926 logic input pins requires that many external connections be made to use this board. 

To reduce the number of necessary external connections, the board has seven default-overriding jumpers. All of the default-overriding jumpers are tied to VDD, except the D1 jumpers, which are tied to GND. 

All **VDD jumper** pads **are circles**; the **ground jumper** pads **are square**. 

Note that the board has only one invert, slew, and enable pin; each of these three pins affects both motor drivers.

| 	**PIN**	|	**Default State**	|	**Description**	|
|-----------|-----------------------|-------------------|
|	**VIN**		|	HIGH			| This is the main 5 V to 28 V motor power supply connection, which should typically be made to the larger VIN pad. Operation from 5 V to 8 V reduces maximum current output; the device is also protected for transients up to 40 V. The smaller VIN pad can be used to distribute the VIN node to the rest of the application circuit; for lower-current applications, the pin can also be used to power the board and motors.|
|	**GND**	|    LOW	|	Ground connection for logic and motor power supplies.|
|	**OUT2**	|	HIGH	|	The motor output pin controlled by IN2.	|
|	**OUT1**	|	HIGH	|	The motor output pin controlled by IN1. |
|	**VDD**		|	HIGH	|	3V to 5V logic supply connection. This pin is used only for the SF pull-up and default-overriding jumpers; in the rare case where none of those features is used, VDD can be left disconnected. |
|	**IN2**		|	HIGH	|	The logic input control of OUT2. PWM can be applied to this pin (typically done with both disable lines inactive). <br>IN2: HIGH -> OUT2: V_PWR (VIN)<br />IN2: LOW -> OUT2: PGND |
|	**IN1**		|	HIGH	|	The logic input control of OUT1. PWM can be applied to this pin (typically done with both disable lines inactive).<br /> IN1: HIGH -> OUT1:VIN<br /> |
|	**PWM / D2**	|	LOW	 |	Inverted disable input: when D2 is low, OUT1 and OUT2 are set to high impedance. A D2 PWM duty cycle of 70% gives a motor duty cycle of 70%. Typically, only one of the two disable pins is used, but the default is for both disable pins to be active. |
|	**PWM / D1**	|	HIGH	|	Disable input: when D1 is high, OUT1 and OUT2 are set to high impedance. A D1 PWM duty cycle of 70% gives a motor duty cycle of 30%. Typically, only one of the two disable pins is used, but the default is for both disable pins to be active. |
|	**SF**	|	HIGH	|	Status flag output: an over-current (short circuit) or over-temperature event will cause SF to be latched LOW. If either of the disable pins (D1 or D2) are disabling the outputs, SF will also be LOW. Otherwise, this pin is weakly pulled high. This allows the two SF pins on the board to be tied together and connected to a single MCU input. |
|	**FB**	|	LOW	|	The FB output provides analog current-sense feedback of approximately 525 mV per amp (only active while H-bridge is driving). |
|	**EN**	|	LOW	|	Enable input: when EN is LOW, the both motor driver ICs are in a low-current sleep mode. |
|	**SLEW**	|	LOW	|	Output slew rate selection input. A logical LOW results in a slow output rise time (1.5 μs to 6 μs). A logical HIGH selects a fast output rise time (0.2 μs to 1.45 μs). This pin should be set HIGH for high-frequency (over 10 kHz) PWM. This pin determines the slew rate mode for both motor driver ICs. 	|
|	**INV**		|	LOW	| A logical high value inverts the meaning of IN1 and IN2 for both motor drivers.<br>Cuando INV=LOW, IN1=LOW $\rightarrow$ OUT1=GND<br>Cuando INV=HIGH, IN1=LOW $\rightarrow$ OUT1=VIN, |



## MC33926 Motor Driver Carrier (Liga Pololu)

Es la opción single del driver.**

https://www.pololu.com/product/1212

17.95  USD

