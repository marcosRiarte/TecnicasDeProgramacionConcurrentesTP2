#ifndef MENSAJES_H_
#define MENSAJES_H_

#define	PETICION	 1
#define	RESPUESTA	 2
#define ALTA         3
#define MODIFICACION 4
#define TRANSACCION_SIZE 20
#define NOMBRE_SIZE	61
#define DIRECCION_SIZE 120
#define TELEFONO_SIZE 13


typedef struct mensaje {
	long mtype;

	int id;
	char estadoDeTransaccion[TRANSACCION_SIZE];
	char nombre[NOMBRE_SIZE];
	char direccion [DIRECCION_SIZE];
	char telefono [TELEFONO_SIZE];
} mensaje;

#endif /* MENSAJES_H_ */
