/*
 * m2m.c
 *
 *  Created on: Aug 7, 2017
 *      Author: Carlos Miguens
 */

#include "m2m.h"
#include "sapi.h"

char replyTemperature[MAXBUFFERM2M];
char replyHumidity[MAXBUFFERM2M];
char replyMove[MAXBUFFERM2M];
char replyLight1[MAXBUFFERM2M];
char replyLight2[MAXBUFFERM2M];
char replyKey1[MAXBUFFERM2M];
char replyKey2[MAXBUFFERM2M];
char replyFan[MAXBUFFERM2M];

uartMap_t MyUART = UART_USB;
int UART_SPEED = 115200;

char overflowBuffer = 0;

int addMessage(char type, void *value)
{
	char data[MAXBUFFERM2M];
	itoa( (int *) value, data, 10);
	switch (type)
	{
	case PREFIX_TEMPERATURE:
		replyTemperature[0] = PREFIX_TEMPERATURE;
		replyTemperature[1] = '=';
		strcpy(&replyTemperature[2], data);
		break;
	case PREFIX_HUMIDITY:
		replyHumidity[0] = PREFIX_HUMIDITY;
		replyHumidity[1] = '=';
		strcpy(&replyHumidity[2], data);
		break;
	case PREFIX_MOVE:
		replyMove[0] = PREFIX_MOVE;
		replyMove[1] = '=';
		strcpy(&replyMove[2], data);
		break;
	case PREFIX_LIGHT1:
		replyLight1[0] = PREFIX_LIGHT1;
		replyLight1[1] = '=';
		strcpy(&replyLight1[2], data);
		break;
	case PREFIX_LIGHT2:
		replyLight2[0] = PREFIX_LIGHT2;
		replyLight2[1] = '=';
		strcpy(&replyLight2[2], data);
		break;
	case PREFIX_KEY1:
		replyKey1[0] = PREFIX_KEY1;
		replyKey1[1] = '=';
		strcpy(&replyKey1[2], data);
		break;
	case PREFIX_KEY2:
		replyKey2[0] = PREFIX_KEY2;
		replyKey2[1] = '=';
		strcpy(&replyKey2[2], data);
		break;
	case PREFIX_FAN:
		replyFan[0] = PREFIX_FAN;
		replyFan[1] = '=';
		strcpy(&replyFan[2], data);
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
		case PREFIX_KEY1:
			uartWriteString(MyUART, replyKey1);
			break;
		case PREFIX_KEY2:
			uartWriteString(MyUART, replyKey2);
			break;
		}

	}

	TerminateTask();
}

void initM2M(void)
{
	addMessage(PREFIX_KEY1, 0);
	addMessage(PREFIX_KEY2, 0);
	addMessage(PREFIX_TEMPERATURE, 0);
	addMessage(PREFIX_HUMIDITY, 0);
	addMessage(PREFIX_MOVE, 0);
	addMessage(PREFIX_LIGHT1, 0);
	addMessage(PREFIX_LIGHT2, 0);
	addMessage(PREFIX_FAN, 0);
	uartConfig( MyUART, UART_SPEED );
}
