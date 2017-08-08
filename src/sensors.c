/*
 * sensors.c
 *
 *  Created on: Aug 1, 2017
 *      Author: Carlos Miguens
 */

#include "sensors.h"
#include "sapi.h"
#include "os.h"       // <= freeOSEK
#include "HTU21DF.h"
#include "m2m.h"

#define sMOTION GPIO0

int movAntiBounce;
int wetAntiBounce;
int k1AntiBounce;
int k2AntiBounce;

void sensorsTask(void)
{
	char msgM2M[5];
	state = 0;
/*	int temperature = HTU21DF_readTemperature();
	float wet = HTU21DF_readHumidity();
	if (wet > 96) state = state | sWET;
*/
	movAntiBounce = (gpioRead( sMOTION ))? movAntiBounce + 1 : 0;
	if (movAntiBounce > 10 ) {
		movAntiBounce--; // avoid overflow
		state = state | sMOVE;
	}

	if (!gpioRead( TEC1 )) state = state | sKEY1;
	if (!gpioRead( TEC2 )) state = state | sKEY2;
	if (!gpioRead( TEC4 )) state = state | sWET;

	msgM2M[0] = 'S';
	msgM2M[1] = (state | sMOVE)?'1':'0';
	msgM2M[2] = !gpioRead( TEC1 )?'1':'0';
	msgM2M[3] = !gpioRead( TEC2 )?'1':'0';
	msgM2M[4] = !gpioRead( TEC4 )?'1':'0';

	addMessage(msgM2M);

	TerminateTask();
}

void initSensors(void)
{
	// Motion sensor
	gpioConfig( sMOTION, GPIO_INPUT );
	// Humidity sensor
	HTU21DF_initI2C();
	HTU21DF_begin();
	// init sensors state
	state = 0;
	movAntiBounce = 0;
	wetAntiBounce = 0;
	k1AntiBounce = 0;
	k2AntiBounce = 0;
}
