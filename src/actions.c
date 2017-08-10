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

int moveDelay = 0;
int moveWait = 200;

void actionsTask(void)
{
	char msgM2M[5];
	moveDelay = (move)?moveWait:moveDelay-1;
	moveDelay = (moveDelay < 0)?0:moveDelay; // void overflow

	gpioWrite(LEDB, key1);
	gpioWrite(LED1, key2);
	gpioWrite(LED2, moveDelay);
	gpioWrite(LED3, humidity);

	TerminateTask();
}

void initActions(void)
{

}
