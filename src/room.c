/*============================================================================
 * Licencia: 
 * Autor: Carlos Miguens
 * Fecha: Jul 26 2017
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK
#define sMOTION GPIO0

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
   
   // Init motion sensor
   gpioConfig( sMOTION, GPIO_INPUT );

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

#define sMOVE 1
#define sWET  2
#define sKEY1 3
#define sKEY2 4
int state;

TASK(HumanMachineTask)
{
	TerminateTask();
}


TASK(ActionTask)
{
	gpioWrite(LEDB, state & (1 << sKEY1));
	gpioWrite(LED1, state & (1 << sKEY2));
	gpioWrite(LED2, state & (1 << sMOVE));
	gpioWrite(LED3, state & (1 << sWET));
	// terminate task
	TerminateTask();
}

TASK(SensorTask)
{
	state = 0;
	state = state | (!gpioRead( TEC1 ) << sKEY1);
	state = state | (!gpioRead( TEC2 ) << sKEY2);
	state = state | (gpioRead( sMOTION ) << sMOVE);
	state = state | (!gpioRead( TEC4 ) << sWET);

	// terminate task
	TerminateTask();
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
