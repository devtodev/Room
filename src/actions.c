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
	moveDelay = (state & sMOVE)?moveWait:moveDelay-1;
	moveDelay = (moveDelay < 0)?0:moveDelay; // void overflow

	gpioWrite(LEDB, state & sKEY1);
	gpioWrite(LED1, state & sKEY2);
	gpioWrite(LED2, (moveDelay > 0));
	gpioWrite(LED3, state & sWET);

	msgM2M[0] = 'M';
	msgM2M[1] = (state & sKEY1)?'1':'0';
	msgM2M[2] = (state & sKEY2)?'1':'0';
	msgM2M[3] = (moveDelay > 0)?'1':'0';
	msgM2M[4] = (state & sWET)?'1':'0';

	addMessage(msgM2M);

	TerminateTask();
}

void initActions(void)
{

}
