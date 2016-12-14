#include "osObjects.h"					// RTOS object definitions
#include "Board_LED.h"                  // ::Board Support:LED
#include "rl_net.h"                     // Keil.MDK-Pro::Network:CORE


extern void hardware_init(void);
extern void InitSensorThread(void);

void BlinkLED(uint32_t color);

enum
{
	Green = 0,
	Red = 1, 
	Blue = 2
} LedColor;

int main (void)
{
	osKernelInitialize ();				// Initialize CMSIS-RTOS
	
	hardware_init();								
	LED_Initialize();
	InitSensorThread();					
	netInitialize();
	
	osKernelStart();					// Start thread execution
	
	while(1)
	{
		BlinkLED(Blue);
	}
}

void BlinkLED(uint32_t color)
{			
	osDelay(500);
	LED_On(color);						
	osDelay(500);
	LED_Off(color);
}
