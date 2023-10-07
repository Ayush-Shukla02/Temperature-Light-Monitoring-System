# Temperature and Light Montoring System

## Introduction

The primary goal of this project is to create a temperature and light monitoring system. The program has been developed using a Tiva C Board and other sensor like LM35 and LDR. Voltage divider method is used for getting the LDR readings where one resistance is used as a reference resistance and LDR’s resistance is used to calculate the surrounding light level. The project uses VCC (5V), Ground, ADC PE3, PE2 and TIMER to accurately measure the data.

## Components

-   Tiva TM4C123GH6PM Microcontroller
-   Tools: IAR Embedded Workbench
-   LM35 Temperature Sensor
-   LDR (Light Dependent Resistor)
-   Resistors

## Working

-   The LM35 sensor has been used to measure the temperature of the surrounding environment, while the LDR sensor is used to detect the light levels of the surrounding. A threshold temperature value of 33 degrees has been set, above which the red LED of the microcontroller blinks to indicate that
    the temperature is high.
-   A Voltage Divider Circuit has been used a voltage divider circuit for the LDR sensor, which will convert the resistance of the LDR to a voltage value that can be measured by the microcontroller. The output of the voltage divider circuit is fed into an analog input pin on the TM4C123GH6PM
    microcontroller.
-   The microcontroller reads the voltage output from the LM35 sensor and converts it to a temperature value. This temperature value is compared to the temperature threshold value to determine if the temperature is too high. The microcontroller reads the voltage output from the LDR sensor and converts it to a light value.
-   The Green LED on the Breadboard indicates whether the light intensity is high or low. If the light intensity is high, the green LED will be turned off, otherwise it will be turned on.
-   The Red LED on the microcontroller indicates whether the temperature is high or low. If the temperature is high, the red LED will blink, otherwise it will be turned off.

## Output

For the results refer to the [output](./Photos) folder.
