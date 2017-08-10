/*
 * m2m.h
 *
 *  Created on: Aug 7, 2017
 *      Author: Carlos Miguens
 */

#ifndef APPLICATION_ROOM_SRC_M2M_H_
#define APPLICATION_ROOM_SRC_M2M_H_

#define PREFIX_KEY1			  'K'
#define PREFIX_KEY2			  'k'
#define PREFIX_TEMPERATURE    'T'
#define PREFIX_HUMIDITY       'H'
#define PREFIX_MOVE    		  'M'
#define PREFIX_LIGHT1         'L'
#define PREFIX_LIGHT2    	  'l'
#define PREFIX_FAN    		  'F'

#define PREFIX_SET    		  '='

#define MAXBUFFERM2M 	   8

void m2mTask(void);
void initM2M(void);
int addMessage(char type, void *value);

#endif /* APPLICATION_ROOM_SRC_M2M_H_ */
