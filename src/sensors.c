/*
 * sensors.c
 *
 *  Created on: Aug 1, 2017
 *      Author: Carlos Miguens
 */

#include "sensors.h"

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#define sMOTION GPIO0


int movAntiBounce;
int wetAntiBounce;
int k1AntiBounce;
int k2AntiBounce;

void sensorsTask(void)
{
	state = 0;

	movAntiBounce = (gpioRead( sMOTION ))? movAntiBounce + 1 : 0;

	if (!gpioRead( TEC1 )) state = state | sKEY1;
	if (!gpioRead( TEC2 )) state = state | sKEY2;

	if (movAntiBounce > 10 ) {
		movAntiBounce--; // avoid the overflow
		state = state | sMOVE;
	}

	if (!gpioRead( TEC4 )) state = state | sWET;

	// terminate task
	TerminateTask();
}

void initSensors(void)
{
	// Init motion sensor
	gpioConfig( sMOTION, GPIO_INPUT );

	// init sensors state
	state = 0;
	movAntiBounce = 0;
	wetAntiBounce = 0;
	k1AntiBounce = 0;
	k2AntiBounce = 0;
}
