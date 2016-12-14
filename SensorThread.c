#include "cmsis_os.h"                                           
#include "Board_Accelerometer.h"        // ::Board Support:Accelerometer
#include "Board_Magnetometer.h"         // ::Board Support:Magnetometer

void SensorThread(void const *argument);

osThreadId threadId;
osThreadDef(SensorThread, osPriorityNormal, 1, 0);

ACCELEROMETER_STATE accelerometerState;
MAGNETOMETER_STATE magnetometerState;

int InitSensorThread(void)
{
	threadId = osThreadCreate(osThread(SensorThread), NULL);
	return !threadId ? -1 : 0;
}

void SensorThread(void const *argument)
{
	Accelerometer_Initialize();
	Magnetometer_Initialize();
	
	while(1)
	{
		Accelerometer_GetState(&accelerometerState);
		Magnetometer_GetState(&magnetometerState);
		osDelay(100);	
	}
}
