/*
 * inputs.c
 *
 *  Created on: 5 jun. 2022
 *      Author: Hongo
 */
#include "inputs.h"
#include "Passenger.h"

/**
*brief Imprime el menu principal y llama a getNumero para obtener la opcion requerida por el usuario
*
*
* \return Devuelve la opcion ingresada
*/
int printMenuPrincipal(){

		int auxOpcionMenuPrincipal;
		printf("\n--MENU--\n");
		printf("\n[1] Cargar los datos de los pasajeros desde el archivo data.csv (modo texto)");
		printf("\n[2] Cargar los datos de los pasajeros desde el archivo data.csv (modo binario)");
		printf("\n[3] Alta de pasajero");
		printf("\n[4] Modificar datos de pasajero");
		printf("\n[5] Baja de pasajero");
		printf("\n[6] Listar pasajeros");
		printf("\n[7] Ordenar pasajeros");
		printf("\n[8] Guardar los datos de los pasajeros en el archivo data.csv (modo texto)");
		printf("\n[9] Guardar los datos de los pasajeros en el archivo data.csv (modo binario)\n");
		printf("\n[10] INFORMES\n");
		printf("\n[11] Salir");

		utn_getNumero(&auxOpcionMenuPrincipal, "", "\nIngrese una opcion valida.", 1, 11, 5);

		return auxOpcionMenuPrincipal;

}
/**
*brief Imprime el menu de modificaciones y llama a getNumero para obtener la opcion requerida por el usuario
*
*
* \return Devuelve la opcion ingresada
*/
int printMenuModificaciones(){
		int auxOpcionMenuPrincipal;
		printf("\n-INGRESE LA OPCIÓN QUE DESEE REALIZAR-\n");
		printf("\n[1] Modificar nombre");
		printf("\n[2] Modificar apellido");
		printf("\n[3] Modificar precio");
		printf("\n[4] Modificar codigo de vuelo");
		printf("\n[5] Modificar tipo de pasajero");
		printf("\n[6] Modificar estado de vuelo");
		printf("\n[10] Salir");

		utn_getNumero(&auxOpcionMenuPrincipal, "", "\nIngrese una opcion valida.", 1, 10, 5);

		return auxOpcionMenuPrincipal;

}
/**
*brief Imprime el menu de de ordenamiento y llama a getNumero para obtener la opcion requerida por el usuario
*
*
* \return Devuelve la opcion ingresada
*/
int printMenuSort(){
		int auxOpcionMenuPrincipal;
		printf("\n-MENU DE ORDENAMIENTO-\n");
		printf("\n[1] Ordenar por ID");
		printf("\n[2] Ordenar por NOMBRE");
		printf("\n[3] Ordenar por APELLIDO");
		printf("\n[4] Ordenar por PRECIO");
		printf("\n[5] Ordenar por CODIGO DE VUELO");
		printf("\n[6] Ordenar por TIPO DE PASAJERO");
		printf("\n[7] Ordenar por ESTADO DE VUELO");
		printf("\n[10] Salir");

		utn_getNumero(&auxOpcionMenuPrincipal, "", "\nIngrese una opcion valida.", 1, 10, 5);

		return auxOpcionMenuPrincipal;

}

int esNumerica(char *cadena, int limite);
int getInt(int *pResultado);
int getString(char *cadena, int longitud);

/** \brief Valida si el string recibido es una palabra A-Z, a-z
 *
 * \param string
 * \return Devuelve 0 si es una palabra, -1 Si no lo es.
 */
int validateWordChar(char string[]) {
	int retorno = -1;
	int i = 0;
	if (string != NULL) {
		if (string[strnlen(string, 50) - 1] == '\n') {
			string[strnlen(string, 50) - 1] = '\0';
		}
		while (string[i] != '\0') {
			if (!(isalpha(string[i]))) {
				retorno = -1;
				break;
			} else {
				retorno = 0;
			}
			i++;
		}
	}
	return retorno;
}
/** \brief Obtiene un string, y valida si el string recibido es una palabra A-Z, a-z
* \param *cadena puntero a string
* \param *mensaje Recibe el mensaje a mostrar
* \param *mensajeError Recibe el mensaje de error
* \param len
* \return Devuelve 0 si esta ok, -1 Si no pudo obtener el string
*/
int getValidWord(char *cadena, char *mensaje, char *mensajeError, int len) {
	char auxCadena[len];
	int validacion;
	if (mensaje != NULL && mensajeError != NULL && len > 0) {
		do {
			printf("%s", mensaje);
			fgets(auxCadena, len, stdin);
			if (auxCadena[strnlen(auxCadena, len) - 1] == '\n') {
				auxCadena[strnlen(auxCadena, len) - 1] = '\0';
			}
			if (validateWordChar(auxCadena) == -1) {
				printf("%s", mensajeError);
				fflush(stdin);
				validacion = -1;
			} else {
				validacion = 0;
			}
		} while (validacion == -1);
	}
	strncpy(cadena, auxCadena, len);
	return 0;
}
/**
 * \brief Solicita un float al usuario, leuego de verificarlo devuelve el resultado
 * \param char *numeroChar
 * \param char *mensaje Es el mensaje a ser mostrado
 * \param char *mensajeError Es el mensaje de Error a ser mostrado
 * \param int len Largo maximo del float
 * \return 0 si se obtuvo el numero y -1 si no
 *
 */
int getValidFloatChar(char *numeroChar, char *mensaje, char *mensajeError, int len) {
	char charNumero[len];
	int validacion;
	if (mensaje != NULL && mensajeError != NULL && len > 0) {
			do {
				printf("%s", mensaje);
				fgets(charNumero, len, stdin);
				if(charNumero[strnlen(charNumero, 50)-1] == '\n'){
					charNumero[strnlen(charNumero, 50)-1] = '\0';
				}
				if (validateFloatChar(charNumero) == -1) {
					printf("%s", mensajeError);
					fflush(stdin);
					validacion = -1;
				} else {
					validacion = 0;
				}
			} while (validacion == -1);
		}
		strcpy(numeroChar, charNumero);
		return validacion;
	}
/**
 * \brief Solicita un numero al usuario, leuego de verificarlo devuelve el resultado
 * \param float *numero
 * \param char *mensaje Es el mensaje a ser mostrado
 * \param char *mensajeError Es el mensaje de Error a ser mostrado
 * \param int len Largo maximo del float
 * \return 0 si se obtuvo el numero y -1 si no
 *
 */
int getValidFloat(float *numero, char *mensaje, char *mensajeError, int len) {
	char charNumero[len];
	float numeroFinal;
	int validacion;
	if (mensaje != NULL && mensajeError != NULL && len > 0) {
			do {
				printf("%s", mensaje);
				fgets(charNumero, len, stdin);
				if(charNumero[strnlen(charNumero, 50)-1] == '\n'){
					charNumero[strnlen(charNumero, 50)-1] = '\0';
				}
				if (validateFloatChar(charNumero) == -1) {
					printf("%s", mensajeError);
					fflush(stdin);
					validacion = -1;
				} else {
					validacion = 0;
				}
			} while (validacion == -1);
			numeroFinal = atof(charNumero);
		}
		*numero = numeroFinal;
		return 0;
	}

/** \brief Valida si el string recibido contiene solo numeros y hasta un "." que
 * divida en dos mitades (formato tipo flotante)
 *
 * \param string
 * \return Devuelve 0 si respeta el formato, -1 si no lo es
 */
int validateFloatChar(char string[]) {
	fflush(stdin);
	int retorno = -1;
	int i = 0;
	int contadorPuntos = 0;
	if (string != NULL) {
		if (string[strnlen(string, 50) - 1] == '\n') {
			string[strnlen(string, 50) - 1] = '\0';
		}
		while (string[i] != '\0') {
			if (string[i] == '.') {
				contadorPuntos++;
				if (contadorPuntos > 1) {
					retorno = -1;
					break;
				}
			}
			if (!(string[i] >= 48 && string[i] <= 57) && (string[i] != '.')) {
				retorno = -1;
				break;
			} else {
				retorno = 0;
			}
			i++;
		}
	}
	return retorno;
}
int utn_getNumero(int *pResultado, char *mensaje, char *mensajeError,
		int minimo, int maximo, int reintentos) {
	int retorno = -1;
	int bufferInt;
	do {
		printf("%s", mensaje);
		if (getInt(&bufferInt) == 0 && bufferInt >= minimo
				&& bufferInt <= maximo) {
			retorno = 0;
			*pResultado = bufferInt;
			break;
		}
		printf("%s", mensajeError);
		reintentos--;
	} while (reintentos >= 0);

	return retorno;
}
/**
 *brief Utiliza las funciones getString y esNumerica, para obtener y validar
 *brief una cadena como numero respectivamente, si salio ok,
 *brief transforma la cadena en un entero.
 *
 * * \param *cadena
 * * \param *limite
 * \return Devuelve 0 si esta ok, -1 Si fallo
 */
int getInt(int *pResultado) {
	int retorno = -1;
	char bufferString[50];
	if (pResultado != NULL && getString(bufferString, sizeof(bufferString)) == 0
			&& esNumerica(bufferString, sizeof(bufferString))) {
		retorno = 0;
		*pResultado = atoi(bufferString);

	}
	return retorno;
}

/**
 *brief Verifica si la cadena recibida es numerica, si contiene solo
 *brief los caracteres "1 al 9", "+" y "-"
 *
 * * \param *cadena
 * * \param *limite
 * \return Devuelve 0 si esta ok, -1 Si fallo
 */
int esNumerica(char *cadena, int limite) {
	int retorno = -1; // ERROR
	int i;
	if (cadena != NULL && limite > 0) {
		retorno = 1; // VERDADERO
		for (i = 0; i < limite && cadena[i] != '\0'; i++) {
			if (i == 0 && (cadena[i] == '+' || cadena[i] == '-')) {
				continue;
			}
			if (cadena[i] < '0' || cadena[i] > '9') {
				retorno = 0;
				break;
			}
			//CONTINUE
		}
		//BREAK
	}
	return retorno;
}
/**
*brief Obtiene un numero entero y positivo
*
* \param int *numero
* \param char *mensaje Es el mensaje a ser mostrado
* \param char *mensajeError Es el mensaje de Error a ser mostrado
* \param int len Largo maximo
*  * \param int reintentos
* \return Devuelve 0 si esta ok, -1 Si fallo
*/
int getValidPositiveInt(int *numero, char *mensaje, char *mensajeError, int len, int reintentos) {
	char charNumero[len];
	int numeroFinal;
	int retorno;
	if (mensaje != NULL && mensajeError != NULL && len > 0) {
		do {
			printf("%s", mensaje);
			fgets(charNumero, len, stdin);
			if (charNumero[strnlen(charNumero, 50) - 1] == '\n') {
				charNumero[strnlen(charNumero, 50) - 1] = '\0';
			}
			if (esNumericaPositiva(charNumero) == -1) {
				printf("%s", mensajeError);
				fflush(stdin);
				retorno = -1;
				reintentos--;
			} else {
				retorno = 0;
			}
		} while (retorno == -1 && reintentos > 0);
		numeroFinal = atoi(charNumero);
	}
	*numero = numeroFinal;
	return retorno;
}
/**
*brief Verifica si la cadena recibida es numerica y positiva, si contiene solo
*los caracteres "1 al 9", "+" y "-"
*
* * \param *cadena
* \return Devuelve 0 si esta ok, -1 Si fallo
*/
int esNumericaPositiva(char *cadena) {
	int retorno = -1;
	int i;
	int limite;
	limite = strlen(cadena);
	if (cadena != NULL && limite > 0) {
		retorno = 1;
		for (i = 0; i < limite && cadena[i] != '\0'; i++) {
			if (cadena[i] < '0' || cadena[i] > '9') {
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 *brief Obtiene un string, reemplaza los caracteres correspondientes
 *brief al enter si los encuentra, y los reemplaza con el caracter terminante
 *brief de la cadena
 *
 * * \param *cadena
 * * \param *longitud
 * \return Devuelve 0 si esta ok, -1 Si fallo
 */
int getString(char *cadena, int longitud) {
	int retorno = -1;
	char bufferString[4096];
	if (cadena != NULL && longitud > 0) {
		fflush(stdin);
		if (fgets(bufferString, sizeof(bufferString), stdin) != NULL) {
			if (bufferString[strnlen(bufferString, sizeof(bufferString)) - 1]
					== '\n') {
				bufferString[strnlen(bufferString, sizeof(bufferString)) - 1] =
						'\0';
			}
			if (strnlen(bufferString, sizeof(bufferString)) <= longitud) {
				strncpy(cadena, bufferString, longitud);
				retorno = 0;
			}
		}
	}
	return retorno;
}
/**
*brief Obtiene un string, Verifica que sean solo espacios o letras A-Z
*
* \param char *string
* \param int len
* \param char *mensaje
* \param char *mensajeError
* \param int reintentos
* \return Devuelve 0 si esta ok, -1 Si fallo
*/
int getEspaciosYLetras(char *string, int len, char *mensaje, char *mensajeError,
		int reintentos) {
	int retorno = -1;
	char bufferString[len];

	if (string != NULL && len > 0) {
		printf("%s", mensaje);
		do {
			if (getString(bufferString, sizeof(bufferString)) == 0
					&& isName(bufferString) == 1) {
				strncpy(string, bufferString, sizeof(bufferString));
				retorno = 0;
				break;

			} else {
				reintentos--;
				if (reintentos > 0) {
					printf("%s", mensajeError);
				} else {
					printf("\n-Se quedo sin reintentos-\n");
				}
			}
		} while (reintentos > 0);
	}
	return retorno;
}
/**
*brief Verifica si la cadena recibida Es un nombre
*
* * \param char *string
* \return Devuelve 1 si es, 0 si no es
*/
int isName(char *string) { //retorna 1 si es alfa, 0 si no
	int retorno = 1;
	int i = 0;
	int isAlpha;

	if (string != NULL) {
		while (string[i] != '\0') {
			isAlpha = isalpha(string[i]);
			if (isAlpha != 0 || string[i] == ' ') {
				i++;
			} else {
				retorno = 0;
				break;
			}
		}
	}

	return retorno;
}
/**
*brief Verifica si la cadena recibida Es un Flycode
*
* * \param char *string
* \return Devuelve 1 si es, 0 si no es
*/
int isFlycode(char *string) { // retorna 1 si es flycode, 0 si no
	int retorno = 1;
	int i = 0;
	int isAlpha;
	int isDigit;

	if (string != NULL) {
		while (string[i] != '\0') {
			isAlpha = isalpha(string[i]);
			isDigit = isdigit(string[i]);
			if ((isAlpha != 0 || isDigit != 0) && strlen(string) == 7) {
				i++;
			} else {
				retorno = 0;
				break;
			}
		}
	} else {
		retorno = -1;
	}

	return retorno;
}
/**
*brief Obtiene un Flycode, lo devuelve por parametro
*
* \param char *string
* \param int len
* \param char *mensaje
* \param char *mensajeError
* \param int reintentos
* \return Devuelve 0 si OK, -1 si fallo
*/
int getFlyCode(char *string, int len, char *mensaje, char *mensajeError,
		int reintentos) {
	int retorno = -1;
	char flyCodeStr[len];

	if (string != NULL && mensaje != NULL && mensajeError != NULL && len > 0) {
		do {
			printf("%s", mensaje);
			if (getString(flyCodeStr, sizeof(flyCodeStr)) == 0
					&& isFlycode(flyCodeStr) == 1) {
				strcpy(string, flyCodeStr);
				retorno = 0;
				break;

			} else {
				reintentos--;
				if (reintentos > 0) {
					printf("%s", mensajeError);
				} else {
					printf("\n-Se quedo sin reintentos-\n");
				}
			}
		} while (reintentos > 0);
	}
	return retorno;
}
/**
*brief Obtiene un StatusFlight, lo devuelve por parametro
*
* \param char *string
* \param int len
* \param char *mensaje
* \param char *mensajeError
* \param int reintentos
* \return Devuelve 0 si OK, -1 si fallo
*/
int getStatusFlight(char *string, char *mensaje, char *mensajeError,
		int reintentos) {
	int retorno = -1;
	char statusFlightStr[11];

	if (string != NULL && mensaje != NULL && mensajeError != NULL) {
		do {
			printf("%s", mensaje);
			if (getString(statusFlightStr, sizeof(statusFlightStr)) == 0
					&& isStatusFlight(statusFlightStr) == 1) {
				for(int i = 0; i < strlen(statusFlightStr); i++){
					if(i == 0){
						statusFlightStr[i] = toupper(statusFlightStr[i]);
					} else if (statusFlightStr[i-1] == ' '){
						statusFlightStr[i] = toupper(statusFlightStr[i]);
					} else{
						statusFlightStr[i] = tolower(statusFlightStr[i]);
					}
				}
				strcpy(string, statusFlightStr);
				retorno = 0;
				break;

			} else {
				reintentos--;
				if (reintentos > 0) {
					printf("%s", mensajeError);
				} else {
					printf("\n-Se quedo sin reintentos-\n");
				}
			}
		} while (reintentos > 0);
	}
	return retorno;
}
/**
*brief Verifica si la cadena recibida Es un estado de vuelo valido
*
* * \param char *string
* \return Devuelve 1 si es, 0 si no es
*/
int isStatusFlight(char *string) { // retorna 1 si es statusflight, 0 si no;
	int retorno = -1;

	if (string != NULL) {

		if(stricmp(string, "En vuelo") == 0 || stricmp(string, "Aterrizado") == 0 ||  stricmp(string, "En Horario") == 0 || stricmp(string, "Demorado") == 0){
			retorno = 1;
		} else{
			retorno = 0;
		}



	}
	return retorno;
}
/**
*brief Obtiene un tipo de pasajero en formato string, y lo devuelve como char[]
*
* \param char *string
* \param int len
* \param char *mensaje
* \param char *mensajeError
* \param int reintentos
* \return Devuelve 0 si OK, -1 si fallo
*/
int getTypePassengerChar(char *string, char *mensaje, char *mensajeError, int reintentos){
	int retorno = -1;
	char typePassengerStr[15];
	int typePassenger;

	if (string != NULL && mensaje != NULL && mensajeError != NULL) {
		if (utn_getNumero(&typePassenger, mensaje, mensajeError,
				1, 3, reintentos) == 0) {
			if(Passenger_IntToTypePassenger(typePassenger, typePassengerStr) == 0){
				strcpy(string, typePassengerStr);
				retorno = 0;
			}
		}
	}

	return retorno;
}

/** \brief Recibe el id a asignar a un pasajero, pide los datos de ese pasajero por input,
 * y llama a Passenger_newParametros, pasandole los datos obtenidos
* \param char *idUnico
* \return retorna un puntero al pasajero
*
*/
Passenger* Passenger_pedirDatosYCrearUnPasajero(char *idUnico) {
	char nombreStr[51];
	char apellidoStr[51];
	char precioStr[8];
	char flyCodeStr[8];
	char typePassengerStr[15];
	char statusFlightStr[11];
	Passenger *punteroAUnPasajero = NULL;
	if (getEspaciosYLetras(nombreStr, 51,
			"\nIntroduzca el nombre del pasajero: ",
			"\n-Ingrese un nombre valido-\n", 5) == 0
			&& getEspaciosYLetras(apellidoStr, 51,
					"\nIntroduzca el apellido del pasajero: ",
					"\n-Ingrese un apellido valido-\n", 5) == 0
			&& getValidFloatChar(precioStr,
					"\nIntroduzca el precio del pasaje del pasajero:",
					"\n-Ingrese un precio valido-\n", 8) == 0
			&& getFlyCode(flyCodeStr, 8,
					"\nIntroduzca el codigo de vuelo del pasajero [Alfanumerico maximo 7 digitos]: ",
					"\n-Ingrese un codigo de vuelo valido-\n", 5) == 0
			&& getTypePassengerChar(
					typePassengerStr, //corregir
					"\nIntroduzca el tipo de pasajero [1- EconomyClass, 2- EjecutiveClass, 3- FirstClass]: ",
					"\n-Ingrese un tipo de pasajero valido-\n", 5) == 0
			&& getStatusFlight(statusFlightStr,
					"\nIntroduzca el estado de vuelo del pasajero:\n['En horario', 'Demorado', 'En vuelo', 'Aterrizado'] ",
					"\n-Ingrese un estado de vuelo valido-\n", 5) == 0) {
		punteroAUnPasajero = Passenger_newParametros(idUnico, nombreStr,
				apellidoStr, precioStr, flyCodeStr, typePassengerStr,
				statusFlightStr);
	}

	return punteroAUnPasajero;
}
