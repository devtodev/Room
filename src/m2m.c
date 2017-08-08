/*
 * m2m.c
 *
 *  Created on: Aug 7, 2017
 *      Author: Carlos Miguens
 */

#include "m2m.h"
#include "sapi.h"

#define PREFIX_SENSORS    'S'
#define PREFIX_M2M_STATES 'M'
#define PREFIX_ACTIONS    'A'
#define MAXBUFFERM2M 	   5

char replySensors[MAXBUFFERM2M], replyStates[MAXBUFFERM2M], replyActions[MAXBUFFERM2M];

uartMap_t MyUART = UART_USB;
int UART_SPEED = 115200;

char overflowBuffer = 0;

int addMessage(char msg[5])
{
	switch (msg[0])
	{
		case PREFIX_SENSORS:
			strcpy(replySensors, msg);
		break;
		case PREFIX_M2M_STATES:
			strcpy(replyStates, msg);
		break;
		case PREFIX_ACTIONS:
			strcpy(replyActions, msg);
		break;
	}
}

#define MAXINBUFF 50

void m2mTask(void)
{
	char inBuff[MAXINBUFF];
	char in, i = 0;

	// read
	while ((uartReadByte(MyUART, &in)) && (i < MAXINBUFF))
	{
		inBuff[i] = in;
		i++;
	}
	// response
	if (i > 0)
	{
		switch (inBuff[0])
		{
			case PREFIX_SENSORS:
				uartWriteString(MyUART, replySensors);
				break;
			case PREFIX_M2M_STATES:
				uartWriteString(MyUART, replyStates);
				break;
			case PREFIX_ACTIONS:
				uartWriteString(MyUART, replyActions);
				break;
		}
	}

	TerminateTask();
}

void initM2M(void)
{
	uartConfig( MyUART, UART_SPEED );
}
