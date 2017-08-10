/*
 * m2m.c
 *
 *  Created on: Aug 7, 2017
 *      Author: Carlos Miguens
 */

#include "m2m.h"
#include "sapi.h"

#define PREFIX_TEMPERATURE    'T'
#define PREFIX_HUMIDITY       'H'
#define PREFIX_MOVE    		  'M'
#define PREFIX_LIGHT1         'L'
#define PREFIX_LIGHT2    	  'l'
#define PREFIX_FAN    		  'F'

#define PREFIX_GET		      '<'
#define PREFIX_SET    		  '='

#define MAXBUFFERM2M 	   5

char replyTemperature[MAXBUFFERM2M],
 	 replyHumidity[MAXBUFFERM2M],
 	 replyMove[MAXBUFFERM2M];
	 replyLight1[MAXBUFFERM2M],
	 replyLight2[MAXBUFFERM2M],
	 replyFan[MAXBUFFERM2M];

uartMap_t MyUART = UART_USB;
int UART_SPEED = 115200;

char overflowBuffer = 0;

int addMessage(char msg[5])
{
	switch (msg[0])
	{
	case PREFIX_TEMPERATURE:
		strcpy(replyTemperature, msg);
		break;
	case PREFIX_HUMIDITY:
		strcpy(replyHumidity, msg);
		break;
	case PREFIX_MOVE:
		strcpy(replyMove, msg);
		break;
	case PREFIX_LIGHT1:
		strcpy(replyLight1, msg);
		break;
	case PREFIX_LIGHT2:
		strcpy(replyLight2, msg);
		break;
	case PREFIX_FAN:
		strcpy(replyFan, msg);
		break;
	}

	return 0;
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
		case PREFIX_TEMPERATURE:
			uartWriteString(MyUART, replyTemperature);
			break;
		case PREFIX_HUMIDITY:
			uartWriteString(MyUART, replyHumidity);
			break;
		case PREFIX_MOVE:
			uartWriteString(MyUART, replyMove);
			break;
		case PREFIX_LIGHT1:
			if (inBuff[1] == PREFIX_SET)
			{
				replyLight1[0] = PREFIX_LIGHT1;
				replyLight1[1] = inBuff[2];
				replyLight1[2] = '\0';
			}
			uartWriteString(MyUART, replyLight1);
			break;
		case PREFIX_LIGHT2:
			if (inBuff[1] == PREFIX_SET)
			{
				replyLight2[0] = PREFIX_LIGHT2;
				replyLight2[1] = inBuff[2];
				replyLight2[2] = '\0';
			}
			uartWriteString(MyUART, replyLight2);
			break;
		case PREFIX_FAN:
			if (inBuff[1] == PREFIX_SET)
			{
				replyFan[0] = PREFIX_FAN;
				replyFan[1] = inBuff[2];
				replyFan[2] = '\0';
			}
			uartWriteString(MyUART, replyFan);
			break;
		}

	}

	TerminateTask();
}

void initM2M(void)
{
	uartConfig( MyUART, UART_SPEED );
}
