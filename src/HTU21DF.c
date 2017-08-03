/*
 * HTU21DF.c
 *
 *  Created on: Aug 2, 2017
 *      Author: Carlos Miguens
 *
 *  Driver for HTU21D-F humidity and temperature sensor for EDU-CIAA NXP
 *
 */


/** \addtogroup i2c I2C Example
** @{ */

/*==================[inclusions]=============================================*/
#include "HTU21DF.h"
#include "board.h"
#include "sapi.h"

/*==================[macros and definitions]=================================*/

/** i2c port used */
#define I2C_PORT I2C0

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

void HTU21DF_reset(void);
int write_I2C_HTU21DF(uint8_t wbuf);
int read_I2C_HTU21DF(uint8_t wbuf, uint8_t *rbuf, int rxBuffSize);
void delayHTU21DF();

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

int write_I2C_HTU21DF(uint8_t wbuf)
{
	I2C_XFER_T xfer;
	xfer.rxBuff = 0;
	xfer.rxSz = 0;
	xfer.slaveAddr = HTU21DF_I2CADDR;
	xfer.status = 0;
	xfer.txBuff = &wbuf;
	xfer.txSz = 1;
	Chip_I2C_MasterTransfer(I2C_PORT, &xfer);
	return 0;
}

int read_I2C_HTU21DF(uint8_t wbuf, uint8_t *rbuf, int rxBuffSize)
{
	I2C_XFER_T xfer;
	xfer.rxBuff = rbuf;
	xfer.rxSz = rxBuffSize;
	xfer.slaveAddr = HTU21DF_I2CADDR;
	xfer.status = 0;
	xfer.txBuff = 0;
	xfer.txSz = 0;

	Chip_I2C_MasterTransfer(I2C_PORT, &xfer);
	return 0;
}

void delayHTU21DF()
{
	int i;
	//delay por software calculado con el teorema de los cinco dedos oscilantes
	for(i=0; i<0xFFFF; i++);
}


/*==================[external functions definition]==========================*/

int HTU21DF_initI2C()
{
	Board_I2C_Init(I2C_PORT);
	Chip_I2C_SetClockRate(I2C_PORT, 100000);
	Chip_I2C_SetMasterEventHandler(I2C_PORT, Chip_I2C_EventHandlerPolling);
	return 0;
}

int HTU21DF_begin(void)
{
	uint8_t rbuf[3] = {0,0,0};
	HTU21DF_reset();
	delayHTU21DF();
	delayHTU21DF();
	delayHTU21DF();
	delayHTU21DF();
	delayHTU21DF();
	write_I2C_HTU21DF(HTU21DF_READREG);
	delayHTU21DF();
	delayHTU21DF();
	delayHTU21DF();
	delayHTU21DF();
	delayHTU21DF();
	read_I2C_HTU21DF(HTU21DF_READREG, rbuf, 1);
	return rbuf[0];
}

void HTU21DF_reset(void)
{
	delayHTU21DF();
	write_I2C_HTU21DF(HTU21DF_RESET);
	delayHTU21DF();
}

float HTU21DF_readTemperature(void)
{
	uint16_t rbuf[3];
	float temp = 0;
	uint16_t t = 0;

	write_I2C_HTU21DF(HTU21DF_READTEMP);
	delayHTU21DF();
	delayHTU21DF();
	delayHTU21DF();
	read_I2C_HTU21DF(HTU21DF_READTEMP, rbuf, 3);
	t = rbuf[0];
	t <<= 8;
	t |= rbuf[1];
	temp = t;
	temp *= 175.72;
	temp /= 65536;
	temp -= 46.85;
	return temp;
}

float HTU21DF_readHumidity(void)
{
	uint16_t rbuf[3];
	float hum = 0;
	uint16_t h = 0;

	write_I2C_HTU21DF(HTU21DF_READHUM);
	delayHTU21DF();
	delayHTU21DF();
	delayHTU21DF();
	read_I2C_HTU21DF(HTU21DF_READHUM, rbuf, 3);
	h = rbuf[0];
	h <<= 8;
	h |= rbuf[1];
	hum = h;
	hum *= 125;
	hum /= 65536;
	hum -= 6;

	return hum;
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/
