// lABORATORIO 5
//6. When Tiva receives the message from 5, a buzzer should be activated for
//2 seconds.


#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.c"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

void Delay(uint32_t);

char data[100];

int main(void)
{
    // Configuración del reloj del sistema a 120 MHz
    SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480, 120000000);
    
      
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        // Habilitar los puertos GPIO N, F y J y A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    
        // Verifica si los periféricos están habilitados
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)){}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)){}
    
        // Habilitar los GPIO N y F para los LEDs
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    
    /*----------GPIO DECLARATION----------*/
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); // PF2 para LED externo

    /*----------UART DECLARATION----------*/  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, 0x03);
    UARTStdioConfig(0, 9600, 120000000);
    
    while(1)
    {
        /*----------UART IMPLEMENTATION----------*/
        if (UARTCharsAvail(UART0_BASE))
        {
            UARTgets(data, 100);
            UARTprintf("Mensaje recibido: %s\n", data); // Muestra el mensaje recibido

            // Encender LED en PF2 si se recibe la palabra "led"
            if (strcmp(data, "buzzer") == 0)
            {
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); // Enciende el LED
                SysCtlDelay((120000000 / 3)*0.2);  // Delay de 1 segundo
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
            }
            else
            {
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); // Apaga el LED si se recibe otra cosa
            }
        }
        
        Delay(100);
    }
}

void Delay(uint32_t time)
{
    SysCtlDelay(40000 * time);
}

