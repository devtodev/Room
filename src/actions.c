/*
 * actions.c
 *
 *  Created on: Aug 1, 2017
 *      Author: Carlos Miguens
 */

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "sensors.h"
#include "actions.h"
#include "m2m.h"

#define swLight1 GPIO2
#define swLight2 GPIO4
#define swFan 	 GPIO6

int moveDelay = 0;
int fanDelay = 0;
int timeToWait = 10;

void actionsTask(void)
{
	// the following lines allow to move event stay ON for a while
	moveDelay = (move || key1)?timeToWait:moveDelay-1;
	moveDelay = (moveDelay < 0)?0:moveDelay; // void overflow

	fanDelay = (key2)?timeToWait:fanDelay-1;
	fanDelay = (fanDelay < 0)?0:fanDelay;

	gpioWrite(LED2, moveDelay);
	gpioWrite(swLight1, moveDelay);

	gpioWrite(LED3, fanDelay);
	gpioWrite(swFan, humidity || fanDelay);

	TerminateTask();
}

void initActions(void)
{
	gpioConfig( swLight1, GPIO_OUTPUT );
	gpioConfig( swLight2, GPIO_OUTPUT );
	gpioConfig( swFan, GPIO_OUTPUT );
}
