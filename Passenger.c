#include "Passenger.h"


/** \brief Crea una direccion de memoria para alojar un pasajero. Inicializa todos sus valores en 0.
*
* \return Passenger * Retorna un puntero al pasajero.
*
*/
Passenger* Passenger_new() {

	Passenger *punteroAUnPasajero;
	punteroAUnPasajero = (Passenger*) malloc(sizeof(Passenger));

	Passenger_setId(punteroAUnPasajero, 0);
	Passenger_setNombre(punteroAUnPasajero, " ");
	Passenger_setApellido(punteroAUnPasajero, " ");
	Passenger_setPrecio(punteroAUnPasajero, 0);
	Passenger_setFlyCode(punteroAUnPasajero, " ");
	Passenger_setTypePassenger(punteroAUnPasajero, 0);
	Passenger_setStatusFlight(punteroAUnPasajero, " ");

	return punteroAUnPasajero;

}
/** \brief Llama a Passenger_new, convierte los valores recibidos como string en el tipo de dato correspondiente
* y los setea en el puntero indicado. Si sale mal, borra ese pasajero.
*
* \param char* idStr
* \param char* nombreStr
* \param char* apellidoStr
* \param char* precioStr
* \param char* flyCodeStr
* \param char* idStr
* \param char* typePassengerStr
* \param char* statusFlightStr
* \return Passenger* devuelve un puntero al pasajero seteado.
*
*/
Passenger* Passenger_newParametros(char *idStr, char *nombreStr,
		char *apellidoStr, char *precioStr, char *flyCodeStr,
		char *typePassengerStr, char *statusFlightStr) {
	Passenger *punteroAUnPasajero;
	int auxIdAtoi;
	float auxPrecioAtof;
	int auxTypePassengerAtoi;
	punteroAUnPasajero = Passenger_new();
	if (punteroAUnPasajero != NULL) {
		if (idStr != NULL && nombreStr != NULL && apellidoStr != NULL
				&& precioStr != NULL && flyCodeStr != NULL
				&& typePassengerStr != NULL && statusFlightStr != NULL) {
			if (Passenger_charToNum(idStr, precioStr, typePassengerStr,
					&auxIdAtoi, &auxPrecioAtof, &auxTypePassengerAtoi) == 0) {
				if (Passenger_setId(punteroAUnPasajero, auxIdAtoi) != 0
						|| Passenger_setNombre(punteroAUnPasajero, nombreStr)
								!= 0
						|| Passenger_setApellido(punteroAUnPasajero,
								apellidoStr) != 0
						|| Passenger_setPrecio(punteroAUnPasajero,
								auxPrecioAtof) != 0
						|| Passenger_setFlyCode(punteroAUnPasajero, flyCodeStr)
								!= 0
						|| Passenger_setTypePassenger(punteroAUnPasajero,
								auxTypePassengerAtoi) != 0
						|| Passenger_setStatusFlight(punteroAUnPasajero,
								statusFlightStr) != 0) {
					Passenger_delete(punteroAUnPasajero);
					punteroAUnPasajero = NULL;

				}
			} else {
				printf("No se pudieron convertir los datos");
			}
		}
	}
	return punteroAUnPasajero;
}
/** \brief Elimina la direccion de memoria del puntero a pasajero recibido.
*
* \return void
*
*/
void Passenger_delete(Passenger *this) {
	if (this != NULL) {
		free(this);
	}
}
/** \brief Llama a todos los setters y setea todos los valores recibidos en el pasajero "this"
* \param Passenger *this
* \param int id
* \param char *nombre
* \param char *apellido
* \param float precio
* \param char *flyCode
* \param int typePassenger
* \param char *statusFlight
* \return 0 si ok, -1 si falla
*
*/
int Passenger_setAllElements(Passenger *this, int id, char *nombre,
		char *apellido, float precio, char *flyCode, int typePassenger,
		char *statusFlight) {
	int retorno = -1;

	if (this != NULL && Passenger_setId(this, id) == 0
			&& Passenger_setNombre(this, nombre) == 0
			&& Passenger_setApellido(this, apellido)
			&& Passenger_setPrecio(this, precio) == 0
			&& Passenger_setFlyCode(this, flyCode) == 0
			&& Passenger_setTypePassenger(this, typePassenger) == 0
			&& Passenger_setStatusFlight(this, statusFlight) == 0) {

		retorno = 0;
	}

	return retorno;
}

/** \brief Llama a todos los getters y devuelve por parametro todos los valores obtenidos del pasajero "this"
* \param Passenger *this
* \param int *id
* \param char *nombre
* \param char *apellido
* \param float *precio
* \param char *flyCode
* \param int *typePassenger
* \param char *statusFlight
* \return 0 si ok, -1 si falla
*
*/
int Passenger_getAllElements(Passenger *this, int *id, char *nombre,
		char *apellido, float *precio, char *flyCode, int *typePassenger,
		char *statusFlight) {
	int retorno = -1;

	int auxId;
	char auxNombre[51];
	char auxApellido[51];
	float auxPrecio;
	char auxFlyCode[8];
	int auxTypePassenger;
	char auxStatusFlight[11];
	if (this != NULL && Passenger_getId(this, &auxId) == 0
			&& Passenger_getNombre(this, auxNombre) == 0
			&& Passenger_getApellido(this, auxApellido) == 0
			&& Passenger_getPrecio(this, &auxPrecio) == 0
			&& Passenger_getFlyCode(this, auxFlyCode) == 0
			&& Passenger_getTypePassenger(this, &auxTypePassenger) == 0
			&& Passenger_getStatusFlight(this, auxStatusFlight) == 0) {
		retorno = 0;
	}
	*id = auxId;
	strcpy(nombre, auxNombre);
	strcpy(apellido, auxApellido);
	*precio = auxPrecio;
	strcpy(flyCode, auxFlyCode);
	*typePassenger = auxTypePassenger;
	strcpy(statusFlight, auxStatusFlight);

	return retorno;
}
/** \brief Setea el id obtenido en el pasajero "this"
* \param Passenger *this
* \param int id
* \return 0 si ok, -1 si falla
*
*/
int Passenger_setId(Passenger *this, int id) {
	int retorno = -1;
	if (this != NULL && id > 0) {
		this->id = id;
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene el id del pasajero "this"
* \param Passenger *this
* \param int *id
* \return 0 si ok, -1 si falla
*
*/
int Passenger_getId(Passenger *this, int *id) {
	int retorno = -1;
	if (this != NULL && id != NULL) {
		*id = this->id;
		retorno = 0;
	}
	return retorno;
}
/** \brief Setea el nombre obtenido en el pasajero "this" y lo devuelve por parametros
* \param Passenger *this
* \param char *nombre
* \return 0 si ok, -1 si falla
*
*/
int Passenger_setNombre(Passenger *this, char *nombre) {
	int retorno = -1;
	if (this != NULL && nombre != NULL) {
		strncpy(this->nombre, nombre, sizeof(this->nombre));
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene el nombre del pasajero "this" y lo devuelve por parametros
* \param Passenger *this
* \param char *nombre
* \return 0 si ok, -1 si falla
*
*/
int Passenger_getNombre(Passenger *this, char *nombre) {
	int retorno = -1;
	if (this != NULL && nombre != NULL) {
		strcpy(nombre, this->nombre);
		retorno = 0;
	}
	return retorno;
}
/** \brief Setea el apellido obtenido en el pasajero "this"
* \param Passenger *this
 * \param char *apellido
 * \return 0 si ok, -1 si falla
 *
 */
int Passenger_setApellido(Passenger *this, char *apellido) {
	int retorno = -1;
	if (this != NULL && apellido != NULL) {
		strncpy(this->apellido, apellido, sizeof(this->apellido));
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene el apellido del pasajero "this" y lo devuelve por parametros
 * \param Passenger *this
 * \param char *apellido
 * \return 0 si ok, -1 si falla
 *
 */
int Passenger_getApellido(Passenger *this, char *apellido) {
	int retorno = -1;
	if (this != NULL && apellido != NULL) {
		strcpy(apellido, this->apellido);
		retorno = 0;
	}
	return retorno;
}
/** \brief Setea el precio obtenido en el pasajero "this"
* \param Passenger *this
* \param float precio
* \return 0 si ok, -1 si falla
*
*/
int Passenger_setPrecio(Passenger *this, float precio) {
	int retorno = -1;
	if (this != NULL && precio > 0) {
		this->precio = precio;
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene el precio del pasajero "this" y lo devuelve por parametros
* \param Passenger *this
* \param float *precio
* \return 0 si ok, -1 si falla
*
*/
int Passenger_getPrecio(Passenger *this, float *precio) {
	int retorno = -1;
	if (this != NULL && precio != NULL) {
		*precio = this->precio;
		retorno = 0;
	}
	return retorno;
}
/** \brief Setea el flycode obtenido en el pasajero "this"
* \param Passenger *this
* \param char *flyCode
* \return 0 si ok, -1 si falla
*
*/
int Passenger_setFlyCode(Passenger *this, char *flyCode) {
	int retorno = -1;
	if (this != NULL && flyCode != NULL && isFlycode(flyCode) == 1) {
		strncpy(this->flyCode, flyCode, sizeof(this->flyCode));
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene el flycode del pasajero "this" y lo devuelve por parametros
* \param Passenger *this
* \param char *flyCode
* \return 0 si ok, -1 si falla
*
*/
int Passenger_getFlyCode(Passenger *this, char *flyCode) {
	int retorno = -1;
	if (this != NULL && flyCode != NULL) {
		strcpy(flyCode, this->flyCode);
		retorno = 0;
	}
	return retorno;
}
/** \brief Setea el tipo de pasajero obtenido en el pasajero "this"
* \param Passenger *this
* \param int typePassenger
* \return 0 si ok, -1 si falla
*
*/
int Passenger_setTypePassenger(Passenger *this, int typePassenger) {
	int retorno = -1;
	if (this != NULL && typePassenger > 0) {
		this->typePassenger = typePassenger;
		retorno = 0;
	}
	return retorno;
}
/** \brief Obtiene el tipo de pasajero del pasajero "this" y lo devuelve por parametros
* \param Passenger *this
* \param int *typePassenger
* \return 0 si ok, -1 si falla
*
*/
int Passenger_getTypePassenger(Passenger *this, int *typePassenger) {
	int retorno = -1;
	if (this != NULL && typePassenger != NULL) {
		*typePassenger = this->typePassenger;
		retorno = 0;
	}
	return retorno;
}
/** \brief Setea el estado de vuelo obtenido en el pasajero "this"
* \param Passenger *this
* \param char *statusFlight
* \return 0 si ok, -1 si falla
*
*/
int Passenger_setStatusFlight(Passenger *this, char *statusFlight) {
	int retorno = -1;
	if (this != NULL && statusFlight != NULL) {
		strncpy(this->statusFlight, statusFlight, sizeof(this->statusFlight));
		retorno = 0;
	}
	return retorno;
}
/** \brief Setea el estado de vuelo obtenido en el pasajero "this"
* \param Passenger *this
* \param char *statusFlight
* \return 0 si ok, -1 si falla
*
*/
int Passenger_getStatusFlight(Passenger *this, char *statusFlight) {
	int retorno = -1;
	if (this != NULL && statusFlight != NULL) {
		strcpy(statusFlight, this->statusFlight);
		retorno = 0;
	}
	return retorno;
}
/** \brief Recibe un id y busca el puntero a ese pasajero en la linked list, retorna el indice del mismo
* \param LinkedList *pArrayListPassenger
* \param int idBuscado
* \return retorna el indice del pasajero e la LL, o -1 si falla al encontrarlo
*
*/
int Passenger_findPassengerById(LinkedList *pArrayListPassenger, int idBuscado) {
	int retorno = -1;
	int len;
	int auxId;
	Passenger *punteroUnPasajero = NULL;
	if (pArrayListPassenger != NULL) {
		len = ll_len(pArrayListPassenger);
		for (int i = 0; i < len; i++) {
			punteroUnPasajero = (Passenger*) ll_get(pArrayListPassenger, i);
			Passenger_getId(punteroUnPasajero, &auxId);
			if (auxId == idBuscado) {
				retorno = ll_indexOf(pArrayListPassenger, punteroUnPasajero);
				break;
			}
		}
	}
	return retorno;
}
/** \brief Convierte el tipo de pasajero obtenido como char[] al entero correspondiente a esa cadena.
* Devuelve el int obtenido por parametro.
* \param char *typePassengerStr
* \param int *typePassengerInt
* \return 0 si Ok, -1 si fallo
*
*/
int Passenger_typePassengerToInt(char *typePassengerStr, int *typePassengerInt) {
	int retorno = 0;
	int auxTypePassengerInt;

	if (typePassengerStr != NULL) {

		if (strcmp(typePassengerStr, "EconomyClass") == 0) {
			auxTypePassengerInt = 1;
		} else if (strcmp(typePassengerStr, "ExecutiveClass") == 0) {
			auxTypePassengerInt = 2;
		} else if (strcmp(typePassengerStr, "FirstClass") == 0) {
			auxTypePassengerInt = 3;
		} else {
			retorno = -1;
		}
	}
	*typePassengerInt = auxTypePassengerInt;
	return retorno;
}
/** \brief Convierte el tipo de pasajero obtenido como int al char[] correspondiente a ese numero
* Devuelve el char[] obtenido por parametro.
* \param int *typePassengerInt
* \param char *typePassengerStr
* \return 0 si Ok, -1 si fallo
*
*/
int Passenger_IntToTypePassenger(int typePassengerInt, char *typePassengerStr) {
	int retorno = -1;
	char auxTypePassengerChar[15];

	if (typePassengerInt > 0 && typePassengerStr != NULL) {

		switch (typePassengerInt) {
		case 1:
			strcpy(auxTypePassengerChar, "EconomyClass");
			retorno = 0;
			break;
		case 2:
			strcpy(auxTypePassengerChar, "ExecutiveClass");
			retorno = 0;
			break;
		case 3:
			strcpy(auxTypePassengerChar, "FirstClass");
			retorno = 0;
			break;
		}
		strcpy(typePassengerStr, auxTypePassengerChar);
	}
	return retorno;
}
/** \brief Convierte los datos tipo char de un pasajero (id, precio, tipo), al tipo de dato
* correspondiente en la LL. Los devuelve por puntero
* \param char *idStr
* \param char *precioStr
* \param char *typePassengerStr
* \param int *id
* \param float *precio
* \param int *typePassenger
* \return 0 si Ok, -1 si fallo
*
*/
int Passenger_charToNum(char *idStr, char *precioStr, char *typePassengerStr,
		int *id, float *precio, int *typePassenger) {
	int retorno = 0;
	int auxIdAtoi;
	float auxPrecioAtof;
	int auxTypePassengerInt;

	if (Passenger_typePassengerToInt(typePassengerStr, &auxTypePassengerInt)
			== 0) {
		if ((auxIdAtoi = atoi(idStr)) == 0
				|| (auxPrecioAtof = atof(precioStr)) == 0) {
			retorno = -1; //si algun conversor sale mal
		} else {
			*id = auxIdAtoi;
			*precio = auxPrecioAtof;
			*typePassenger = auxTypePassengerInt;
		}
	}
	return retorno;
}
/** \brief Imprime un pasajero.
* \param Passenger *this
*
*/
void Passenger_printOnePassenger(Passenger *this) {
	int id;
	char nombre[51];
	char apellido[51];
	float precio;
	char flyCode[8];
	int typePassenger;
	char typePassengerStr[15];
	char statusFlight[11];

	if (this != NULL
			&& Passenger_getAllElements(this, &id, nombre, apellido, &precio,
					flyCode, &typePassenger, statusFlight) == 0) {
		Passenger_IntToTypePassenger(typePassenger, typePassengerStr);
		printf("\n+---------+----------------+----------------+-----------+---------+------------------+----------------+");
		printf("\n|ID       |NOMBRE          |APELLIDO        |PRECIO     |FLYCODE  |TIPO DE PASAJERO  |ESTADO DE VUELO |");
		printf("\n+---------+----------------+----------------+-----------+---------+------------------+----------------+");
		printf("\n| %-8d| %-15s| %-15s| %-10.2f| %-8s| %-17s| %-15s|", id, nombre, apellido, precio, flyCode,
				typePassengerStr, statusFlight);
		printf("\n+---------+----------------+----------------+-----------+---------+------------------+----------------+\n");
	}
}

/** \brief Criterio de ordenamiento por id. Debe ser llamada desde el controller Sort
* Compara los datos requeridos de los 2 pasajeros.
* \param void *pPrimerPasajero
* \param void *pSegundoPasajero
* \return Devuelve 1 si el primer pasajero es mayor que el segundo, -1 caso contrario.
* devuelve 0 si son identicos.
*/
int Passenger_sortById(void *pPrimerPasajero, void *pSegundoPasajero) {
	int retorno = -1;
	int idPrimerPasajero;
	int idSegundoPasajero;
	Passenger *primerPasajero;
	Passenger *segundoPasajero;
	if (pPrimerPasajero != NULL && pSegundoPasajero != NULL) {
		primerPasajero = (Passenger*) pPrimerPasajero;
		segundoPasajero = (Passenger*) pSegundoPasajero;
		Passenger_getId(primerPasajero, &idPrimerPasajero);
		Passenger_getId(segundoPasajero, &idSegundoPasajero);
		if (idPrimerPasajero > idSegundoPasajero) {
			retorno = 1;
		} else {
			if (idPrimerPasajero == idSegundoPasajero) {
				retorno = 0;
			}
		}
	}
	return retorno;
}
/** \brief Criterio de ordenamiento por nombre. Debe ser llamada desde el controller Sort
* Compara los datos requeridos de los 2 pasajeros.
* \param void *pPrimerPasajero
* \param void *pSegundoPasajero
* \return Devuelve 1 si el primer pasajero es mayor que el segundo, -1 caso contrario.
* devuelve 0 si son identicos.
*/
int Passenger_sortByNombre(void *pPrimerPasajero, void *pSegundoPasajero) {
	int retorno;
	char nombrePrimerPasajero[51];
	char nombreSegundoPasajero[51];
	Passenger *PrimerPasajero;
	Passenger *SegundoPasajero;
	if (pPrimerPasajero != NULL && pSegundoPasajero != NULL) {
		PrimerPasajero = (Passenger*) pPrimerPasajero;
		SegundoPasajero = (Passenger*) pSegundoPasajero;
		Passenger_getNombre(PrimerPasajero, nombrePrimerPasajero);
		Passenger_getNombre(SegundoPasajero, nombreSegundoPasajero);
		retorno = strcmp(nombrePrimerPasajero, nombreSegundoPasajero);
	}
	return retorno;
}
/** \brief Criterio de ordenamiento por apellido. Debe ser llamada desde el controller Sort
* Compara los datos requeridos de los 2 pasajeros.
* \param void *pPrimerPasajero
* \param void *pSegundoPasajero
* \return Devuelve 1 si el primer pasajero es mayor que el segundo, -1 caso contrario.
* devuelve 0 si son identicos.
*/
int Passenger_sortByApellido(void *pPrimerPasajero, void *pSegundoPasajero) {
	int retorno;
	char apellidoPrimerPasajero[51];
	char apellidoSegundoPasajero[51];
	Passenger *PrimerPasajero;
	Passenger *SegundoPasajero;
	if (pPrimerPasajero != NULL && pSegundoPasajero != NULL) {
		PrimerPasajero = (Passenger*) pPrimerPasajero;
		SegundoPasajero = (Passenger*) pSegundoPasajero;
		Passenger_getApellido(PrimerPasajero, apellidoPrimerPasajero);
		Passenger_getApellido(SegundoPasajero, apellidoSegundoPasajero);
		retorno = strcmp(apellidoPrimerPasajero, apellidoSegundoPasajero);
	}
	return retorno;
}
/** \brief Criterio de ordenamiento por precio. Debe ser llamada desde el controller Sort
* Compara los datos requeridos de los 2 pasajeros.
* \param void *pPrimerPasajero
* \param void *pSegundoPasajero
* \return Devuelve 1 si el primer pasajero es mayor que el segundo, -1 caso contrario.
* devuelve 0 si son identicos.
*/
int Passenger_sortByPrecio(void *pPrimerPasajero, void *pSegundoPasajero) {
	int retorno = -1;
	float precioPrimerPasajero;
	float precioSegundoPasajero;
	Passenger *primerPasajero;
	Passenger *segundoPasajero;
	if (pPrimerPasajero != NULL && pSegundoPasajero != NULL) {
		primerPasajero = (Passenger*) pPrimerPasajero;
		segundoPasajero = (Passenger*) pSegundoPasajero;
		Passenger_getPrecio(primerPasajero, &precioPrimerPasajero);
		Passenger_getPrecio(segundoPasajero, &precioSegundoPasajero);
		if (precioPrimerPasajero > precioSegundoPasajero) {
			retorno = 1;
		} else {
			if (precioPrimerPasajero == precioSegundoPasajero) {
				retorno = 0;
			}
		}
	}
	return retorno;
}
/** \brief Criterio de ordenamiento por nombre. Debe ser llamada desde el controller Sort.
* Compara los datos requeridos de los 2 pasajeros.
* \param void *pPrimerPasajero
* \param void *pSegundoPasajero
* \return Devuelve 1 si el primer pasajero es mayor que el segundo, -1 caso contrario.
* devuelve 0 si son identicos.
*/
int Passenger_sortByFlycode(void *pPrimerPasajero, void *pSegundoPasajero) {
	int retorno;
	char flycodePrimerPasajero[51];
	char flycodeSegundoPasajero[51];
	Passenger *PrimerPasajero;
	Passenger *SegundoPasajero;
	if (pPrimerPasajero != NULL && pSegundoPasajero != NULL) {
		PrimerPasajero = (Passenger*) pPrimerPasajero;
		SegundoPasajero = (Passenger*) pSegundoPasajero;
		Passenger_getFlyCode(PrimerPasajero, flycodePrimerPasajero);
		Passenger_getFlyCode(SegundoPasajero, flycodeSegundoPasajero);
		retorno = strcmp(flycodePrimerPasajero, flycodeSegundoPasajero);
	}
	return retorno;
}
/** \brief Criterio de ordenamiento por tipo de pasajero. Debe ser llamada desde el controller Sort
* Compara los datos requeridos de los 2 pasajeros.
* \param void *pPrimerPasajero
* \param void *pSegundoPasajero
* \return Devuelve 1 si el primer pasajero es mayor que el segundo, -1 caso contrario.
* devuelve 0 si son identicos.
*/
int Passenger_sortByTypePassenger(void *pPrimerPasajero, void *pSegundoPasajero) {
	int retorno = -1;
	int typePassengerPrimerPasajero;
	int typePassengerSegundoPasajero;
	Passenger *primerPasajero;
	Passenger *segundoPasajero;
	if (pPrimerPasajero != NULL && pSegundoPasajero != NULL) {
		primerPasajero = (Passenger*) pPrimerPasajero;
		segundoPasajero = (Passenger*) pSegundoPasajero;
		Passenger_getTypePassenger(primerPasajero,
				&typePassengerPrimerPasajero);
		Passenger_getTypePassenger(segundoPasajero,
				&typePassengerSegundoPasajero);
		if (typePassengerPrimerPasajero > typePassengerSegundoPasajero) {
			retorno = 1;
		} else {
			if (typePassengerPrimerPasajero == typePassengerSegundoPasajero) {
				retorno = 0;
			}
		}
	}
	return retorno;
}
/** \brief Criterio de ordenamiento por estado de vuelo. Debe ser llamada desde el controller Sort
* Compara los datos requeridos de los 2 pasajeros.
* \param void *pPrimerPasajero
* \param void *pSegundoPasajero
* \return Devuelve 1 si el primer pasajero es mayor que el segundo, -1 caso contrario.
* devuelve 0 si son identicos.
*/
int Passenger_sortByStatusFlight(void *pPrimerPasajero, void *pSegundoPasajero) {
	int retorno;
	char statusFlightPrimerPasajero[51];
	char statusFlightSegundoPasajero[51];
	Passenger *PrimerPasajero;
	Passenger *SegundoPasajero;
	if (pPrimerPasajero != NULL && pSegundoPasajero != NULL) {
		PrimerPasajero = (Passenger*) pPrimerPasajero;
		SegundoPasajero = (Passenger*) pSegundoPasajero;
		Passenger_getStatusFlight(PrimerPasajero, statusFlightPrimerPasajero);
		Passenger_getStatusFlight(SegundoPasajero, statusFlightSegundoPasajero);
		retorno = strcmp(statusFlightPrimerPasajero,
				statusFlightSegundoPasajero);
	}
	return retorno;
}

int Passenger_compareFirstClass(void *pPasajero){
	int retorno = -1;
	int typePassenger;

	if(pPasajero != NULL){
		Passenger_getTypePassenger(pPasajero, &typePassenger);

			if(typePassenger == 3){
				retorno = 1;
			} else {
				retorno = 0;
			}
	}

	return retorno;
}

int Passenger_compareExecutiveClass(void *pPasajero){
	int retorno = -1;
	int typePassenger;
	if(pPasajero != NULL){

		Passenger_getTypePassenger(pPasajero, &typePassenger);

			if(typePassenger == 2){
				retorno = 1;
			} else {
				retorno = 0;
			}

	}
	return retorno;
}

int Passenger_compareEconomyClass(void *pPasajero){
	int retorno = -1;
	int typePassenger;
	if(pPasajero != NULL){
		Passenger_getTypePassenger(pPasajero, &typePassenger);

			if(typePassenger == 1){
				retorno = 1;
			} else {
				retorno = 0;
			}

		}
	return retorno;
}

int Passenger_setMillasAcumuladas(Passenger *this, int millasAcumuladas) {
	int retorno = -1;
	if (this != NULL && millasAcumuladas > 0) {
		this->millasAcumuladas = millasAcumuladas;
		retorno = 0;
	}
	return retorno;
}

int Passenger_getMillasAcumuladas(Passenger *this, int *millasAcumuladas) {
	int retorno = -1;
	if (this != NULL && millasAcumuladas != NULL) {
		*millasAcumuladas = this->millasAcumuladas;
		retorno = 0;
	}
	return retorno;
}

Passenger* calcularMillasAcumuladas(void *pPasajero){
	int millas;
	float precioPasajero;
	int typePassenger;
	Passenger * pasajero = (Passenger*)pPasajero;
	Passenger_getTypePassenger(pasajero, &typePassenger);

	if(pasajero != NULL){
		Passenger_getPrecio(pasajero, &precioPasajero);

		millas = (int)precioPasajero / 100;

		if(typePassenger == 3){
			millas = millas * 2;
		} else if(typePassenger == 2){
			millas = millas * 3;
		}

		Passenger_setMillasAcumuladas(pasajero, millas);

	}


	return pasajero;
}

