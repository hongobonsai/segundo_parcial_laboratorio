#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"
#include "Controller.h"
#include "Inputs.h"

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char *path, LinkedList *pArrayListPassenger) {
	int retorno = -1;
	FILE *file;
	if (pArrayListPassenger != NULL && path != NULL) {
		file = fopen(path, "r");
		if (file != NULL) {
			parser_PassengerFromText(file, pArrayListPassenger);
			retorno = 0;
		} else {
		}
		fclose(file);
	}
	return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char *path, LinkedList *pArrayListPassenger) {
	int retorno = -1;
	FILE *pFile;
	if (path != NULL && pArrayListPassenger != NULL) {
		pFile = fopen(path, "rb");

		if (pFile != NULL) {
			retorno = parser_PassengerFromBinary(pFile, pArrayListPassenger);
		}
		fclose(pFile);
	}
	return retorno;
}

/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_addPassenger(LinkedList *pArrayListPassenger) {
	int retorno = -1;
	char auxIdStr[11];
	int auxIdInt;
	Passenger *pPasajeroACrear;
	if (pArrayListPassenger != NULL) {
		if (parser_LastIdFromText("data_Id.csv", auxIdStr) == 0) {
			auxIdInt = atoi(auxIdStr);
			auxIdInt++;
			snprintf(auxIdStr, 11, "%d", auxIdInt);

			pPasajeroACrear = Passenger_pedirDatosYCrearUnPasajero(auxIdStr);
			if (pPasajeroACrear != NULL) {
				if (controller_saveLastId("data_Id.csv", auxIdStr) == 0) {
					retorno = ll_add(pArrayListPassenger, pPasajeroACrear);
				} else {
					free(pPasajeroACrear);
				}
			}
		}
	}

	return retorno;
}

/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_editPassenger(LinkedList *pArrayListPassenger) {
	int retorno = -1;
	int idBuscado;
	int indiceEncontrado;
	int confirmacion;
	char ultimoIdExistente[11];
	int auxUltimoId;
	Passenger *punteroUnPasajero;

	char nombre[51];
	char apellido[51];
	float precio;
	char flyCode[8];
	int typePassenger;
	char statusFlight[11];

	if (pArrayListPassenger != NULL && !ll_isEmpty(pArrayListPassenger)) {

		if ((utn_getNumero(&confirmacion, "\n-Desea ver la lista de pasajeros? ([1] Si, [2] No)-", "\n-Ingrese una opcion valida-", 1, 2, 5)) == 0) {
			if (confirmacion == 1) {
				controller_ListPassenger(pArrayListPassenger);
			}
		} else {
			printf("\n\n-Se acabaron los reintentos, no se mostrara la lista de pasajeros-\n");
		}

		parser_LastIdFromText("data_Id.csv", ultimoIdExistente);
		auxUltimoId = atoi(ultimoIdExistente);
		printf("\n\nEl ultimo ID ingresado es: %s\n", ultimoIdExistente);

		if (utn_getNumero(&idBuscado, "\nIngrese el ID a modificar\n", "\n-Ingrese una opcion valida-", 1, auxUltimoId, 5) == 0) {
			do {
				if ((indiceEncontrado = Passenger_findPassengerById( pArrayListPassenger, idBuscado)) != -1) {
					punteroUnPasajero = (Passenger*) ll_get(pArrayListPassenger, indiceEncontrado);
					Passenger_printOnePassenger(punteroUnPasajero);
					confirmacion = printMenuModificaciones();

					switch (confirmacion) {
					case 1:
						if (getEspaciosYLetras(nombre, 51, "\nIntroduzca el nuevo nombre del pasajero: ", "\n-Ingrese un nombre valido-\n", 5) == 0) {
							if (Passenger_setNombre(punteroUnPasajero, nombre) == 0) {
								printf("\n\n-Datos modificados correctamente\n");
								retorno = 0;
							}
						}
						break;
					case 2:
						if (getEspaciosYLetras(apellido, 51, "\nIntroduzca el nuevo apellido del pasajero: ", "\n-Ingrese un apellido valido-\n", 5) == 0) {
							if (Passenger_setApellido(punteroUnPasajero, apellido) == 0) {
								printf("\n\n-Datos modificados correctamente\n");
								retorno = 0;
							}
						}
						break;
					case 3:
						if (getValidFloat(&precio, "\nIntroduzca el nuevo precio del pasaje del pasajero: ", "\n-Ingrese un precio valido-\n", 8) == 0) {
							if (Passenger_setPrecio(punteroUnPasajero, precio) == 0) {
								printf("\n\n-Datos modificados correctamente\n");
								retorno = 0;
							}
						}
						break;
					case 4:
						if (getFlyCode(flyCode, 8, "\nIntroduzca el nuevo codigo de vuelo del pasajero [Alfanumerico maximo 7 digitos]: ", "\n-Ingrese un codigo de vuelo valido-\n", 5) == 0) {
							if (Passenger_setFlyCode(punteroUnPasajero, flyCode) == 0) {
								printf("\n\n-Datos modificados correctamente\n");
								retorno = 0;
							}
						}
						break;
					case 5:
						if (utn_getNumero(&typePassenger, "\nIntroduzca el nuevo tipo de pasajero [1- EconomyClass, 2- EjecutiveClass, 3- FirstClass]: ", "\n-Ingrese un tipo de pasajero valido-\n", 1, 3, 5) == 0) {
							if (Passenger_setTypePassenger(punteroUnPasajero, typePassenger) == 0) {
								printf("\n\n-Datos modificados correctamente\n");
								retorno = 0;
							}
						}
						break;
					case 6:
						if (getStatusFlight(statusFlight, "\nIntroduzca el estado de vuelo del pasajero: \n['En horario', 'Demorado', 'En vuelo', 'Aterrizado'] ", "\n-Ingrese un estado de vuelo valido-\n", 5) == 0) {
							if (Passenger_setStatusFlight(punteroUnPasajero, statusFlight) == 0) {
								printf("\n\n-Datos modificados correctamente\n");
								retorno = 0;
							}
						}
						break;
					}
				} else {
					printf("\n-No se encontro al pasajero-\n");
				}

			} while (confirmacion != 10);
		}
	} else {
		printf("\n-La lista de pasajeros está vacia\n");
	}
	return retorno;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_removePassenger(LinkedList *pArrayListPassenger) {
	int retorno = -1;
	int idBorrar;
	int indiceBorrar;
	int confirmacion;
	int respuesta;
	Passenger *punteroUnPasajero;
	char ultimoIdExistente[11];
	int auxUltimoId;
	if ((utn_getNumero(&confirmacion,
			"\n-Desea ver la lista de pasajeros? ([1] Si, [2] No)-",
			"\n-Ingrese una opcion valida-", 1, 2, 5)) == 0) {
		if (confirmacion == 1) {
			controller_ListPassenger(pArrayListPassenger);
		}
		do {

			if (pArrayListPassenger != NULL
					&& !ll_isEmpty(pArrayListPassenger)) {
				parser_LastIdFromText("data_Id.csv", ultimoIdExistente);
				auxUltimoId = atoi(ultimoIdExistente);
				printf("\n\nEl ultimo ID ingresado es: %s\n",
						ultimoIdExistente);
				if (utn_getNumero(&idBorrar, "\nIngrese el ID a borrar\n",
						"\n-Ingrese una opcion valida-", 1, auxUltimoId, 5)
						== 0) {
					if ((indiceBorrar = Passenger_findPassengerById(
							pArrayListPassenger, idBorrar)) != -1) {
						punteroUnPasajero = (Passenger*) ll_get(
								pArrayListPassenger, indiceBorrar);
						Passenger_printOnePassenger(punteroUnPasajero);
						if ((utn_getNumero(&confirmacion,
								"\n-Esta seguro que desea eliminar a este pasajero?([1] Si, [2] No)-",
								"\n-Ingrese una opcion valida-", 1, 2, 5))
								== 0) {
							if (confirmacion == 1) {
								ll_remove(pArrayListPassenger, indiceBorrar);
								Passenger_delete(punteroUnPasajero);
								retorno = 0;
							}
						}
					} else {
						printf("\n-El ID solicitado no existe-\n");
					}

				}
				utn_getNumero(&respuesta,
						"\n-Desea eliminar a otro pasajero?([1] Si, [2] No)-",
						"\n-Ingrese una opcion valida-", 1, 2, 5);
			} else {
				printf("\n-La lista de pasajeros está vacia\n");
			}

		} while (respuesta == 1);
	}
	return retorno;
}

/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_ListPassenger(LinkedList *pArrayListPassenger) {
	int retorno = -1;
	Passenger *punteroAUnPasajero;

	int id;
	char nombre[51];
	char apellido[51];
	float precio;
	char flyCode[8];
	int typePassenger;
	char statusFlight[11];

	char typePassengerStr[15];
	int llLen;

	if (pArrayListPassenger != NULL) {
		llLen = ll_len(pArrayListPassenger);
		if (llLen > 0) {
			printf(
					"\n+---------+----------------+----------------+-----------+---------+------------------+----------------+");
			printf(
					"\n|ID       |NOMBRE          |APELLIDO        |PRECIO     |FLYCODE  |TIPO DE PASAJERO  |ESTADO DE VUELO |");
			printf(
					"\n+---------+----------------+----------------+-----------+---------+------------------+----------------+\n");
			for (int i = 0; i < llLen; i++) {
				punteroAUnPasajero = (Passenger*) ll_get(pArrayListPassenger,
						i);
				Passenger_getAllElements(punteroAUnPasajero, &id, nombre,
						apellido, &precio, flyCode, &typePassenger,
						statusFlight);
				Passenger_IntToTypePassenger(typePassenger, typePassengerStr);
				printf("| %-8d| %-15s| %-15s| %-10.2f| %-8s| %-17s| %-15s|\n",
						id, nombre, apellido, precio, flyCode, typePassengerStr,
						statusFlight);
				retorno = 0;
			}
			printf(
					"+---------+----------------+----------------+-----------+---------+------------------+----------------+\n");
		}

	}

	return retorno;
}

/** \brief Ordenar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_sortPassenger(LinkedList *pArrayListPassenger) {
	int retorno = 0;
	int opcionMenu;
	int opcionOrdenamiento;
	if (pArrayListPassenger != NULL) {
		do {
			opcionMenu = printMenuSort();
			if (opcionMenu != 10) {
				if (utn_getNumero(&opcionOrdenamiento,
						"\nSeleccione un orden de ordenamiento. 0 para descendente o 1 para ascendente\n",
						"\nIngrese un orden valido.", 0, 1, 5) == 0) {
					printf("\n\nOrdenando, por favor espere...\n");
					switch (opcionMenu) {
					case 1:
						ll_sort(pArrayListPassenger, Passenger_sortById,
								opcionOrdenamiento);
						break;
					case 2:
						ll_sort(pArrayListPassenger, Passenger_sortByNombre,
								opcionOrdenamiento);
						break;
					case 3:
						ll_sort(pArrayListPassenger, Passenger_sortByApellido,
								opcionOrdenamiento);
						break;
					case 4:
						ll_sort(pArrayListPassenger, Passenger_sortByPrecio,
								opcionOrdenamiento);
						break;
					case 5:
						ll_sort(pArrayListPassenger, Passenger_sortByFlycode,
								opcionOrdenamiento);
						break;
					case 6:
						ll_sort(pArrayListPassenger,
								Passenger_sortByTypePassenger,
								opcionOrdenamiento);
						break;
					case 7:
						ll_sort(pArrayListPassenger,
								Passenger_sortByStatusFlight,
								opcionOrdenamiento);
						break;
					}
				} else {
					printf("\n\n-No ingreso ninguna opcion valida-\n");
				}

			}
		} while (opcionMenu != 10);
	}
	return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char *path, LinkedList *pArrayListPassenger) {
	int retorno = -1;
	int len = 0;
	FILE *file;
	Passenger *punteroUnPasajero = NULL;
	len = ll_len(pArrayListPassenger);
	int auxId;
	char auxNombre[51];
	char auxApellido[51];
	float auxPrecio;
	char auxFlyCode[8];
	int auxTypePassenger;
	char auxStatusFlight[11];

	char auxTypePassengerStr[15];

	if (path != NULL && pArrayListPassenger != NULL) {
		file = fopen(path, "w");
		if (file != NULL) {
			for (int i = 0; i < len; i++) {
				punteroUnPasajero = (Passenger*) ll_get(pArrayListPassenger, i);
				if (Passenger_getAllElements(punteroUnPasajero, &auxId,
						auxNombre, auxApellido, &auxPrecio, auxFlyCode,
						&auxTypePassenger, auxStatusFlight) == 0
						&& Passenger_IntToTypePassenger(auxTypePassenger,
								auxTypePassengerStr) == 0) {
					fprintf(file, "%d,%s,%s,%d,%s,%s,%s\n", auxId, auxNombre,
							auxApellido, (int) auxPrecio, auxFlyCode,
							auxTypePassengerStr, auxStatusFlight);
					retorno = 0;
				}
			}
		}
	}
	fclose(file);

	return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */

int controller_saveAsBinary(char *path, LinkedList *pArrayListPassenger) {
	int retorno = -1;
	int len;
	FILE *pFile;
	Passenger *punteroUnPasajero = NULL;
	len = ll_len(pArrayListPassenger);

	if (path != NULL && pArrayListPassenger != NULL && len > 0) {
		pFile = fopen(path, "wb");
		if (pFile != NULL) {
			for (int i = 0; i < len; i++) {
				punteroUnPasajero = (Passenger*) ll_get(pArrayListPassenger, i);
				fwrite(punteroUnPasajero, sizeof(Passenger), 1, pFile);
			}
			retorno = 0;
		}
		fclose(pFile);
	}
	return retorno;
}
/** \brief Guarda el ultimo id de los pasajeros en el archivo data_Id.csv.
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveLastId(char *path, char *idParaAsignar) {
	FILE *pFile;
	int retorno = -1;

	pFile = fopen(path, "w");
	if (pFile != NULL) {
		fprintf(pFile, "%s\n", idParaAsignar);
		retorno = 0;
	}
	fclose(pFile);

	return retorno;
}

int controller_ListPassengerMillas(LinkedList *pArrayListPassenger) {
	int retorno = -1;
	Passenger *punteroAUnPasajero;

	int id;
	char nombre[51];
	char apellido[51];
	float precio;
	char flyCode[8];
	int typePassenger;
	char statusFlight[11];
	int millas;

	char typePassengerStr[15];
	int llLen;

	if (pArrayListPassenger != NULL) {
		llLen = ll_len(pArrayListPassenger);
		if (llLen > 0) {
			printf(
					"\n+---------+----------------+----------------+-----------+---------+------------------+----------------+-------------+");
			printf(
					"\n|ID       |NOMBRE          |APELLIDO        |PRECIO     |FLYCODE  |TIPO DE PASAJERO  |ESTADO DE VUELO | MILLAS      |");
			printf(
					"\n+---------+----------------+----------------+-----------+---------+------------------+----------------+-------------+\n");
			for (int i = 0; i < llLen; i++) {
				punteroAUnPasajero = (Passenger*) ll_get(pArrayListPassenger,
						i);
				Passenger_getAllElements(punteroAUnPasajero, &id, nombre,
						apellido, &precio, flyCode, &typePassenger,
						statusFlight);
				Passenger_getMillasAcumuladas(punteroAUnPasajero, &millas);

				Passenger_IntToTypePassenger(typePassenger, typePassengerStr);
				printf("| %-8d| %-15s| %-15s| %-10.2f| %-8s| %-17s| %-15s| %-6dMill  |\n",
						id, nombre, apellido, precio, flyCode, typePassengerStr,
						statusFlight, millas);
				retorno = 0;
			}
			printf(
					"+---------+----------------+----------------+-----------+---------+------------------+----------------+-------------+\n");
		}

	}

	return retorno;
}
