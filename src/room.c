/*============================================================================
 * Licencia: 
 * Autor: Carlos Miguens
 * Fecha: Jul 26 2017
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#include "sensors.h"
#include "actions.h"
#include "HTU21DF.h"
#include "m2m.h"
/*
 * TODO: hacer la implementacion del sensor de humedad I2C
 *
 */

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

/*==================[funcion principal]======================================*/

int main( void )
{
   // Read clock settings and update SystemCoreClock variable
   SystemCoreClockUpdate();

   boardConfig();   
   
   initSensors();
   initM2M();
	// Starts the operating system in the Application Mode 1
	// This example has only one Application Mode
	StartOS(AppMode1);

	// Starts the operating system in the Application Mode 1
	// This example has only one Application Mode
	StartOS(AppMode1);

	// StartOs shall never returns, but to avoid compiler warnings or errors
	// 0 is returned

	return 0;
}


void ErrorHook(void)
{
	ShutdownOS(0);
}

/*
 * The design pattern choised for this project was MVC, Model View Controller.
 *
 * Model is the info measured
 *
 * View is the logic of SensorsTask
 *
 * Controller is the procedures executed in ActionTask
 *
 */

TASK(M2MTask)
{
	m2mTask();
}


TASK(ActionTask)
{
	actionsTask();
}

TASK(SensorTask)
{
	sensorsTask();
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
