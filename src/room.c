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

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();   
   
   initSensors();

   // ---------- INICIAR SISTEMA OPERATIVO --------------------
	// Starts the operating system in the Application Mode 1
	// This example has only one Application Mode
	StartOS(AppMode1);

	// Starts the operating system in the Application Mode 1
	// This example has only one Application Mode
	StartOS(AppMode1);

	// StartOs shall never returns, but to avoid compiler warnings or errors
	// 0 is returned

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta 
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
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

TASK(HumanMachineTask)
{
	TerminateTask();
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
