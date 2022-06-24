#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Passenger.h"
#include "inputs.h"
#include "parser.h"

#define DATA_BIN "data.bin"
#define DATA_CSV "data.csv"

#define ECONOMY_CLASS 1
#define EXECUTIVE_CLASS 2
#define FIRST_CLASS 3

int main() {
	setbuf(stdout, NULL);
	int option = 0;
	int flagCargarAlgo = 0; //0 Para nada cargado, 1 Para Cargado desde add, 2 para Cargado desde archivo
	int flagGuardarAlgo = 0; //0 para nada Guardado, 1 Para Guardado csv, 2 Para Guardaro desde bin
	int llLen;
	int confirmacionExit = 0;
	int opcionInformes;
	int algoFallo = 0;



	int conteoEconomy;
	int conteoExecutive;
	int conteoFirst;
	LinkedList *listaPasajeros = ll_newLinkedList();

	LinkedList *listaClase;
	int lenClase;
	do {
		option = printMenuPrincipal();
		switch (option) {
		case 1: //LISTO
			if (flagCargarAlgo != 2) {
				if (controller_loadFromText(DATA_CSV, listaPasajeros) == 0) {
					printf("\n-El archivo CSV ha sido cargado correctamente-\n");
					flagCargarAlgo = 2;
				}
			} else {
				printf("\nNo se pudo cargar el archivo CSV\n");
			}
			break;
		case 2: //LISTO
			if (flagCargarAlgo != 2) {
				if (controller_loadFromBinary(DATA_BIN, listaPasajeros) == 0) {
					printf("\n-El archivo BIN ha sido cargado correctamente-\n");
					flagCargarAlgo = 2;
				}
			} else {
				printf("\nNo se pudo cargar el archivo BIN\n");
			}
			break;
		case 3: //LISTO
			if (controller_addPassenger(listaPasajeros) == 0) {
				printf("\n-Se agregó al pasajero correctamente-\n");
				flagCargarAlgo = 1;
			} else {
				printf("\n-No se pudo agregar al pasajero-\n");
			}
			break;
		case 4: //LISTO
			if (flagCargarAlgo != 0) {
				if (controller_editPassenger(listaPasajeros) == -1) {
					printf("\n-No se modifico ningun pasajero-\n");
				}
			} else {
				printf(
						"\n-Debe haber algo cargado para realizar una modificacion!-\n");
			}
			break;
		case 5: //LISTO
			if (flagCargarAlgo != 0) {
				controller_removePassenger(listaPasajeros);
				llLen = ll_isEmpty(listaPasajeros);
			} else {
				printf("\n-Debe haber algo cargado para realizar una baja!-\n");
			}
			if (llLen == 1) {
				printf("\n-La lista de pasajeros ahora se encuentra vacia.-\n");
				flagCargarAlgo = 0;
			}
			break;
		case 6: //LISTO
			if (flagCargarAlgo != 0) {
				controller_ListPassenger(listaPasajeros);
			} else {
				printf("\n-No hay pasajeros cargados en la lista");
			}
			break;
		case 7:
			if (flagCargarAlgo != 0) {
				controller_sortPassenger(listaPasajeros);
			} else {
				printf("\n-No hay pasajeros cargados en la lista");
			}
			break;
		case 8: //LISTO
			if (flagCargarAlgo == 2) {
				if(controller_saveAsText(DATA_CSV, listaPasajeros) == 0){
					controller_saveAsBinary(DATA_BIN, listaPasajeros); //Permite que no esten desfasados los archivos. al guardar uno, se actualiza el otro
					printf("\n-Archivo guardado correctamente-\n");
					flagGuardarAlgo = 1;
				}else {
					printf("\n-No se pudo guardar el archivo-\n");
				}
			} else {
				printf("\n-No se puede guardar sin haber cargado antes algun archivo-\n");
			}
			break;
		case 9: //LISTO
			if (flagCargarAlgo == 2) {
				if(controller_saveAsBinary(DATA_BIN, listaPasajeros) == 0){
					controller_saveAsText(DATA_CSV, listaPasajeros); //Permite que no esten desfasados los archivos. al guardar uno, se actualiza el otro
					printf("\n-Archivo guardado correctamente-\n");
					flagGuardarAlgo = 2;
				} else {
					printf("\n-No se pudo guardar el archivo-\n");
				}
			} else {
				printf("\n-No se puede guardar sin haber cargado antes algun archivo-\n");
			}
			break;
		case 10:
			utn_getNumero(&opcionInformes, "\n1. Pasajeros por clase:\n2. Generar archivo de vuelos:\n"
					"3. Calcular millas acumuladas:", "\nIngrese una opcion valida.", 1, 3, 5);
			switch(opcionInformes){
			case 1:
				printf("\nINFORMES\n");

			conteoEconomy = ll_count(listaPasajeros, Passenger_compareEconomyClass);
			conteoExecutive = ll_count(listaPasajeros, Passenger_compareExecutiveClass);
			conteoFirst = ll_count(listaPasajeros, Passenger_compareFirstClass);
			printf("\nCANTIDAD ECONOMY CLASS: %d", conteoEconomy);
			printf("\nCANTIDAD EXECUTIVE CLASS: %d", conteoExecutive);
			printf("\nCANTIDAD FIRST CLASS: %d", conteoFirst);
				break;
			case 2:
					listaClase = ll_filter(listaPasajeros, Passenger_compareFirstClass);
					lenClase = ll_len(listaClase);
					algoFallo = 0;
					controller_ListPassenger(listaClase);
					for(int i = 0; i < lenClase; i++){
						if(controller_saveAsText("CLASES.csv", listaClase) != 0){
							algoFallo = -1;
						}
					}
					if(algoFallo != -1){
						printf("\n-El archivo de pasajeros first class se guardo OK-\n");
					}
				break;
			case 3:
				ll_map(listaPasajeros, calcularMillasAcumuladas);
				controller_ListPassengerMillas(listaPasajeros);
				break;
			}

		break;

		case 11:
			if (flagGuardarAlgo == 0) {
				utn_getNumero(&confirmacionExit,
						"\n-¡No se realizó ningun guardado. Se perderan los cambios-\n  Desea Finalizar? ([1]- SI, [2]- NO)",
						"\n-Ingrese una opción valida-", 1, 2, 5);
			} else {
				confirmacionExit = 1;
			}
			break;
		}
	} while (option != 11 || confirmacionExit != 1);
	printf("\n--EJECUCION FINALIZADA--\n");
	ll_deleteLinkedList(listaPasajeros);
	return 0;
}

