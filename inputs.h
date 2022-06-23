/*
 * inputs.h
 *
 *  Created on: 5 jun. 2022
 *      Author: Hongo
 */

#ifndef INPUTS_H_
#define INPUTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Passenger.h"

int printMenuPrincipal();
int printMenuModificaciones();
int printMenuSort();

Passenger* Passenger_pedirDatosYCrearUnPasajero(char * idUnico);

int isName(char* string);
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int getString(char* cadena, int longitud);
int getValidWord(char *cadena, char *mensaje, char *mensajeError, int len);
int getValidPositiveInt(int *numero, char *mensaje, char *mensajeError, int len,
		int reintentos);
int validateWordChar(char string[]);
int getValidFloatChar(char *numeroChar, char *mensaje, char *mensajeError, int len);
int getValidFloat(float *numero, char *mensaje, char *mensajeError, int len);
int validateFloatChar(char string[]);
int getEspaciosYLetras(char* string, int len, char* mensaje, char* mensajeError, int reintentos);
int esNumericaPositiva(char *cadena);

int getFlyCode(char *string, int len, char *mensaje, char *mensajeError,
		int reintentos);
int getTypePassengerChar(char *string, char *mensaje, char *mensajeError, int reintentos);
int isFlycode(char *string);
int isStatusFlight(char *string);
int getStatusFlight(char *string, char *mensaje, char *mensajeError, int reintentos);
#endif /* INPUTS_H_ */
