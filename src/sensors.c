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

void sensorsTask(void)
{
	temperature = 19; //HTU21DF_readTemperature();
	addMessage(PREFIX_TEMPERATURE, temperature);
	humidity = 93; //HTU21DF_readHumidity();
	addMessage(PREFIX_HUMIDITY, (int) humidity);
	movAntiBounce = (gpioRead( sMOTION ))? movAntiBounce + 1 : 0;
	if (movAntiBounce > 10 ) {
		movAntiBounce--; // avoid overflow
		move = 1;
	} else move = 0;
	addMessage(PREFIX_MOVE, move);

	key1 = (!gpioRead( TEC1 ));
	addMessage(PREFIX_KEY1, key1);
	key2 = (!gpioRead( TEC2 ));
	addMessage(PREFIX_KEY2, key2);

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
	key1 = 0;
	key2 = 0;
	move = 0;
	temperature = 0;
	humidity = 0;
	movAntiBounce = 0;
}
