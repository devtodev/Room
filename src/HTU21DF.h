/*
 * HTU21DF.h
 *
*  Created on: Aug 2, 2017
 *      Author: Carlos Miguens
 *
 *  Driver for HTU21D-F humidity and temperature sensor for EDU-CIAA NXP
 *
 */

#ifndef _HTU21DF_EDU_H_
#define _HTU21DF_EDU_H_
#include "stdint.h"

/** \addtogroup i2c I2C Example
 ** @{ */

/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

#define HTU21DF_I2CADDR     0x40
#define HTU21DF_READTEMP    0xE3
#define HTU21DF_READHUM     0xE5
#define HTU21DF_WRITEREG    0xE6
#define HTU21DF_READREG     0xE7
#define HTU21DF_RESET       0xFE

/*==================[external functions declaration]=========================*/

/** @brief main function
 * @return main function should never return
 */

int HTU21DF_initI2C();
int HTU21DF_begin(void);
float HTU21DF_readTemperature(void);
float HTU21DF_readHumidity(void);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _HTU21DF_H_ */
