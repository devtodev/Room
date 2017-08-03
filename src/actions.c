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

int moveDelay = 0;
int moveWait = 200;

void actionsTask(void)
{
	moveDelay = (state & sMOVE)?moveWait:moveDelay-1;
	moveDelay = (moveDelay < 0)?0:moveDelay; // void overflow

	gpioWrite(LEDB, state & sKEY1);
	gpioWrite(LED1, state & sKEY2);
	gpioWrite(LED2, (moveDelay > 0));
	gpioWrite(LED3, state & sWET);

	TerminateTask();
}

void initActions(void)
{

}
