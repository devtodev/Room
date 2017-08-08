/*
 * m2m.c
 *
 *  Created on: Aug 7, 2017
 *      Author: Carlos Miguens
 */

#include "m2m.h"
#include "sapi.h"

uartMap_t MyUART = UART_USB;
int UART_SPEED = 115200;

#define MAXBUFFERM2M 5

char bufferM2M[MAXBUFFERM2M][MAXBUFFERM2M];
int iBufferM2M = 0, cursorBufferM2M = 0;
char overflowBuffer = 0;

int addMessage(char msg[5])
{
	if (iBufferM2M < MAXBUFFERM2M)
	{
		strcpy(bufferM2M[iBufferM2M], msg);
		iBufferM2M++;
		if (iBufferM2M >= MAXBUFFERM2M)
		{
			overflowBuffer = 1;
			iBufferM2M = 0;
		}
	}
}

void m2mTask(void)
{
	if ((iBufferM2M > 0) || (overflowBuffer == 1))
	{
		uartWriteString(MyUART, bufferM2M[cursorBufferM2M]);

		cursorBufferM2M++;

		if ( ((iBufferM2M <= cursorBufferM2M) && (overflowBuffer == 0)) ||
			(MAXBUFFERM2M <= cursorBufferM2M))
			cursorBufferM2M = 0;
	}

	TerminateTask();
}

void initM2M(void)
{
	uartConfig( MyUART, UART_SPEED );
}
