#include <stdio.h>
#include <string.h>
#include "rl_net.h"
#include "Board_Accelerometer.h"        // ::Board Support:Accelerometer
#include "Board_Magnetometer.h"         // ::Board Support:Magnetometer

extern ACCELEROMETER_STATE accelerometerState;
extern MAGNETOMETER_STATE magnetometerState;

// \brief Generate dynamic web data based on a CGI script.
// \param[in]     env           environment string.
// \param[out]    buf           output data buffer.
// \param[in]     buf_len       size of output buffer (from 536 to 1440 bytes).
// \param[in,out] pcgi          pointer to a session's local buffer of 4 bytes.
//                              - 1st call = cleared to 0,
//                              - 2nd call = not altered by the system,
//                              - 3rd call = not altered by the system, etc.
// \return        number of bytes written to output buffer.
//                - return len | (1U<<31) = repeat flag, the system calls this function
//                                          again for the same script line.
//                - return len | (1U<<30) = force transmit flag, the system transmits
//                                          current packet immediately.
uint32_t netCGI_Script (const char *env, char *buf, uint32_t buf_len, uint32_t *pcgi)
{
	uint32_t len = 0;

	switch (env[0])
	{
		case 'b' :
			sprintf(
				buf, \
				"{\"accelerationX\":\"%d\", \
				\"accelerationY\":\"%d\", \
				\"accelerationZ\":\"%d\", \
				\"magnetometerX\":\"%d\", \
				\"magnetometerY\":\"%d\", \
				\"magnetometerZ\":\"%d\"}", \
				accelerometerState.x, \
				accelerometerState.y, \
				accelerometerState.z, \
				magnetometerState.x, \
				magnetometerState.y, \
				magnetometerState.z);
			len = strlen(buf);
		break;
	}
	
	return (len);
}

const char *netCGX_ContentType (void)
{
	return ("application/json");
}
