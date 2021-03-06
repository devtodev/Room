/*
 * sensors.h
 *
 *  Created on: Aug 1, 2017
 *      Author: Carlos Miguens
 */

#ifndef APPLICATION_ROOM_SRC_SENSORS_H_
#define APPLICATION_ROOM_SRC_SENSORS_H_


#define sMOVE 1
#define sWET  2
#define sKEY1 4
#define sKEY2 8

void sensorsTask(void);
void initSensors(void);

// sensors info
int temperature;
float humidity;
char move, key1, key2;

#endif /* APPLICATION_ROOM_SRC_SENSORS_H_ */
