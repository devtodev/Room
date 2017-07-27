/*============================================================================
 * Licencia: 
 * Autor: Carlos Miguens
 * Fecha: Jul 26 2017
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "sapi.h"     // <= Biblioteca sAPI
#include "os.h"       // <= freeOSEK


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
#define sKEY1 4
#define sKEY2 8
int state;

TASK(PeriodicTask2)
{
	if (state & sMOVE)
	   {
		gpioToggle( LED1 );
	   }
	if (state & sWET)
	   {
		gpioToggle( LED2 );
	   }
	if (state & sKEY1)
	   {
		gpioToggle( LED3 );
	   }
	if (state & sKEY2)
	   {
		gpioToggle( LEDB );
	   }
	state = 0;

	// terminate task
	TerminateTask();
}

TASK(PeriodicTask)
{
	// Movimiento
	if (!gpioRead( TEC1 ))
	{
		state = state | sMOVE;
	}

	// Humedad
	if (!gpioRead( TEC2 ))
	{
		state = state | sWET;
	}

	// Tecla 1
	if (!gpioRead( TEC3 ))
	{
		state = state | sKEY1;
	}

	// Tecla 2
	if (!gpioRead( TEC4 ))
	{
		state = state | sKEY2;
	}

	// terminate task
	TerminateTask();
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Board_Init();
// ciaaIOInit();

/*==================[end of file]============================================*/
