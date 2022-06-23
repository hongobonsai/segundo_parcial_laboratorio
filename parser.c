#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "Inputs.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 * funciona como intermediario entre el archivo csv, las funciones controller y los setters
 * crea o elimina un pasajero, dependiendo de los retornos de las demas funciones.
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE *pFile, LinkedList *pArrayListPassenger) {

	int retorno = -1;
	Passenger *auxPasajero;

	char idStrFile[51];
	char nombreStrFile[51];
	char apellidoStrFile[51];
	char precioStrFile[8];
	char flyCodeStrFile[8];
	char typePassengerStrFile[15];
	char statusFlightStrFile[11];
	if (pFile != NULL && pArrayListPassenger != NULL) {
		do {
			if (fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", idStrFile, nombreStrFile, apellidoStrFile, precioStrFile,
					flyCodeStrFile, typePassengerStrFile, statusFlightStrFile) == 7) {
				auxPasajero = Passenger_newParametros(idStrFile, nombreStrFile, apellidoStrFile, precioStrFile, flyCodeStrFile,
						typePassengerStrFile, statusFlightStrFile);
				if (auxPasajero != NULL) {
					if (ll_add(pArrayListPassenger, auxPasajero) != -1
							&& esNumericaPositiva(idStrFile) == 1
							&& isName(nombreStrFile) == 1
							&& validateFloatChar(precioStrFile) == 0
							&& isFlycode(flyCodeStrFile) == 1
							&& isName(typePassengerStrFile) == 1
							&& esNumericaPositiva(statusFlightStrFile) == 0) {
						retorno = 0;
					} else {
						Passenger_delete(pArrayListPassenger);
						retorno = -1;
					}
				}
			} else {
				break;
				retorno = -2; // Avisa que fallo al leer algun dato.
			}
		} while (!feof(pFile));
	}
	return retorno;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.bin (modo binario).
 * funciona como intermediario entre el archivo bin, las funciones controller y los setters
 * crea o elimina un pasajero, dependiendo de los retornos de las demas funciones.
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger){
	int retorno = -1;
	Passenger* auxPasajero;
	if(pFile != NULL && pArrayListPassenger != NULL) {
		do {
			if((auxPasajero = Passenger_new()) != NULL && fread(auxPasajero, sizeof(Passenger), 1, pFile) == 1) {
					ll_add(pArrayListPassenger, auxPasajero);
					retorno = 0;
			}else {
				if(auxPasajero != NULL) {
					Passenger_delete(auxPasajero);
					}
			}
		} while(!feof(pFile));
	}
	return retorno;
}

/** \brief Rescata el ultimo ID que se encuentra en el archivo data_Id.csv (modo texto).
 * \param path char*
 * \param char *ultimoId
 * \return int
 *
 */
int parser_LastIdFromText(char *path, char *ultimoId) {
	int retorno = -1;
	char auxUltimoId[51];
	FILE *pFile;
	pFile = fopen(path, "r");
	fscanf(pFile, "%[^\n]\n", auxUltimoId); //falsa lectura
	if (pFile != NULL && ultimoId != NULL) {
		fscanf(pFile, "%[^\n]\n", auxUltimoId);
		retorno = 0;
	}
	fclose(pFile);

	strcpy(ultimoId, auxUltimoId);
	return retorno;
}
