#include "TM4C123GH6PM.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define lim 16000000

void delay()
{
    // Set Timer0 to count down from the given value
    TIMER0->CTL = 0;                // Disable Timer0
    TIMER0->CFG = 0;                // 32-bit mode
    TIMER0->TAMR = 0x01;            // One-shot mode
    TIMER0->TAILR = 5 * lim;        // Load the count value
    TIMER0->ICR = 0x01;             // Clear the timeout flag

    // Start Timer0
    TIMER0->CTL |= 0x01;            // Enable Timer0
    while(!(TIMER0->RIS & 0x01));   // Wait for Timer0 timeout

    // Disable Timer0
    TIMER0->CTL = 0;                // Disable Timer0
    TIMER0->ICR = 0x01;             // Clear the timeout flag
}

int main(void)
{
    float voltage1, temp;                                           // Variables for LM35 Readings
    float voltage2, ldrReading, ldrVoltage, ldrResistance, lux;     // Variabels for LDR Readings
    
    // Enable GPIO port E, F and ADC0, ADC1 and TIMER0
    SYSCTL->RCGCGPIO |= (1<<4) | (1<<5);
    SYSCTL->RCGCADC |= (1<<0) | (1<<1);
    SYSCTL->RCGCTIMER |= (1<<0);
    
    // Configure PE3 as ADC input for LM35
    GPIOE->AFSEL |= (1<<3);                 //Enable alternate function
    GPIOE->DEN &= ~(1<<3);                  // Disable digital function
    GPIOE->AMSEL |= (1<<3);                 // Enable analog function
    
    // Configure PE2 as ADC input for LDR
    GPIOE->AFSEL |= (1<<2);                 //Enable alternate function
    GPIOE->DEN &= ~(1<<2);                  // Disable digital function
    GPIOE->AMSEL |= (1<<2);                 // Enable analog function
    
    // RED LED config in GPIOF
    GPIOF->DIR |= (1<<1);
    GPIOF->DEN |= (1<<1);
    
    
    // Configure ADC0
    ADC0->ACTSS &= ~(1<<3);                 // Disable SS3 during configuration
    ADC0->EMUX &= ~0xF000;                  // Software trigger conversion
    ADC0->SSMUX3 = 0;                       // Get input from channel 0
    ADC0->SSCTL3 |= (1<<1) | (1<<2);        //Take one sample at a time
    ADC0->ACTSS |= (1<<3);                  // Enable ADC0 SS3
    
    //configure ADC1
    ADC1->ACTSS &= ~(1<<2);                 // Disable SS2 during configuration
    ADC1->EMUX &= ~0xF000;                  // Software trigger conversion
    ADC1->SSMUX2 = 1;                       // Get input from channel 1
    ADC1->SSCTL2 |= (1<<1)|(1<<2);          //Take one sample at a time
    ADC1->ACTSS |= (1<<2);                  // Enable ADC1 SS2
    
    while(1)
    {
        // For LM35
        ADC0->PSSI |= (1<<3);                   // Start sampling the data
        while((ADC0->RIS & (1<<3)) == 0);       // Wait for conversion to complete
        voltage1 = ADC0->SSFIFO3;               // Read ADC Value
        voltage1 = (voltage1 * 3.3)/4096.0;
        temp = (voltage1 - 0.01) * 100;         // Convert voltage to temperature
        
        if(temp > 33)                           // Check if the temperature is above the limit
            GPIOF->DATA = (1<<1);
        else
            GPIOF->DATA = ~(1<<1);
        
        printf("temp:%f v1:%f\n",temp, voltage1);
         
        // For LDR
        ADC1->PSSI |= (1<<2);                       // Start sampling the data
        while((ADC1->RIS & (1<<2)) == 0) ;          // Wait for conversion to complete 
        ldrReading = ADC1->SSFIFO2;                 // Read adc coversion result from SS2 FIFO
        ADC1->ISC = (1<<2);                         // Clear coversion clear flag bit
        
        voltage2 = (ldrReading*3.3) / 4096;;
        ldrVoltage = 5 - voltage2;
        ldrResistance = ldrVoltage / voltage2 * 10;
        
        printf("v2:%f, ldrv:%f, ldrr:%f\n\n",voltage2, ldrVoltage, ldrResistance);
        
        delay();            // Delay for 5 seconds
    }
}