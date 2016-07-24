# Nuvoton NAU7802 Arduino Library
This library provides readout of the 24-bit SAR ADC. This branch is the ESP8266 version as it needs the pins defined in order to use it.

## Hardware
The pinout of the chip looks as follows. And the connections for reading in two single ended signals.
```
          +-------------------------+
          |                         |
          |   =========U=========   |
          ^---|01 REFP   AVDD 16|---^
       GND----|02 VIN1N  DVDD 15|----3V3
  Signal 1----|03 VIN1P  SDIO 14|----SDA
       GND----|04 VIN2N  SCLK 13|----SCL
  Signal 2----|05 VIN2P  DRDY 12|----
          ----|06 VBG    XOUT 11|----
       GND----|07 REFN    XIN 10|----
       GND----|08 AVSS    DVSS 9|----GND
              ===================
```
The pins functions are described below.

|Pin No. | Pin Name | Type | Description                                       |
| ------:| -------- | ---- | ------------------------------------------------- |
|1       | REFP     | AI   | Positive reference input                          |
|2       | VIN1N    | AI   | Inverting Input #1                                |
|3       | VIN1P    | AI   | Non-Inverting Input #1                            |
|4       | VIN2N    | AI   | Inverting Input #2                                |
|5       | VIN2P    | AI   | Non-Inverting Input #2                            |
|6       | VBG      | A    | High impedance Reference Voltage Output and Bypass|
|7       | REFN     | AI   | Negative Reference Input                          |
|8       | AVSS     | P    | Analog Ground                                     |
|9       | DVSS     | P    | Digital ground                                    |
|10      | XIN      | I    | External crystal oscillator input. TYP 4.9152 MHz |
|11      | XOUT     | O    | External crystal oscillator output                |
|12      | DRDY     | O    | Data Ready Output, a conversion is complete       |
|13      | SCLK     | I    | I2C Clock Input                                   |
|14      | SDIO     | I/O  | I2C Data input                                    |
|15      | DVDD     | P    | Digital power supply: 2.7V ~ 5.5V                 |
|16      | AVDD     | P    | Analog power supply                               |
Note : *TYPE* **P**: Power, **AI**: Analog input, **AO**: Analog output, **I**: input, **O**: output, **I/O**: bi-directional

## Use
In the most basic form, all that is required to use the library is to place the files in the same directory as your Arduino (ino) file. and call the begin and readADC functions.

### Example
Basic code for testing is shown and included in example.

```Arduino
#include "NAU7802.h"

NAU7802 adc = NAU7802();

void setup() {
  Serial.begin(9600);
	adc.begin(2,0);
}

void loop() {
  Serial.println(adc.readADC());
  delay(1000);
}
```

### All Functions
Here is a listing of all functions currently written.

| Returns  | Command                   | Function                               |
| -------- | ------------------------- | -------------------------------------- |
| `boolean`| `begin(sda, scl, addr);`  | Starts up ADC, sets default registers  |
| `long`   | `readADC();`              | Returns preformatted 24 bit ADC value  |
| `void`   | `selectCh1();`            | Selects Channel 1 from internal MUX    |
| `void`   | `selectCh1();`            | Selects Channel 2 from internal MUX    |
| `void`   | `rate010sps();`           | Sets ADC rate to  10 Samples per Second|
| `void`   | `rate020sps();`           | Sets ADC rate to  20 Samples per Second|
| `void`   | `rate040sps();`           | Sets ADC rate to  40 Samples per Second|
| `void`   | `rate080sps();`           | Sets ADC rate to  80 Samples per Second|
| `void`   | `rate320sps();`           | Sets ADC rate to 320 Samples per Second|
