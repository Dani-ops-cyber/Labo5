//lABORATORIO 5 MINIPROYECTO
//cONSIGNA 1 EN TIVA USO DE UART
//Send a message “motor1” or “motor2” using UART when the user switches
//are pressed.

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
uint32_t value;

int main(void)
{
	/*----------CLOCK DECLARATION----------*/
	SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
	
	/*----------GPIO CLOCK ACTIVATION----------*/    
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	
	/*----------GPIO DECLARATION----------*/
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, 0x03);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0x11);

	GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, 0x03);
	GPIOPadConfigSet(GPIO_PORTJ_BASE, 0x03, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	/*----------UART DECLARATION----------*/  
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, 0x03);
	UARTStdioConfig(0,9600,120000000);
	
	while(1)
	{
		/*----------UART IMPLEMENTATION----------*/
		if(GPIOPinRead(GPIO_PORTJ_BASE, 0x01) == 0)
		{
			while((GPIOPinRead(GPIO_PORTJ_BASE, 0x01) == 0))
			{
			}
			UARTprintf("BUTTON 1 PRESSED\n");
			UARTprintf("MOTOR1\n");
		}

		if(GPIOPinRead(GPIO_PORTJ_BASE, 0x02) == 0)
		{
			while((GPIOPinRead(GPIO_PORTJ_BASE, 0x02) == 0))
			{
			}
			UARTprintf("BUTTON 2 PRESSED\n");
			UARTprintf("MOTOR2\n");
		}

		if (UARTCharsAvail(UART0_BASE))
		{
			UARTgets(data,100);
			if(strcmp(data, "PN") == 0)
			{
				GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x03);
				GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x00);
			}
			else
			{
				GPIOPinWrite(GPIO_PORTN_BASE, 0x03, 0x00);
				GPIOPinWrite(GPIO_PORTF_BASE, 0x11, 0x11);
			}
		}
		
		
		
}
		
		Delay(100);
	}


void Delay(uint32_t time){
	SysCtlDelay(40000*time);
}
