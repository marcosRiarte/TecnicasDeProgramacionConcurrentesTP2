#ifndef MENSAJES_H_
#define MENSAJES_H_

static const int PETICION = 1;
static const int RESPUESTA = 2;
static const int ALTA = 3;

static const int SERVER_ID = 1;

static const int NOMBRE_SIZE = 32;
static const int TELEFONO_SIZE = 32;
static const int DIRECCION_SIZE = 32;
static const int TRANSACCION_SIZE = 128;


typedef struct mensaje {
	long mtype;	// Destinatario del mensaje
	long remitente;	// Del mensaje

	int tipo_operacion;

	int id;
	char estadoDeTransaccion[TRANSACCION_SIZE];
	char nombre[NOMBRE_SIZE];
	char direccion [DIRECCION_SIZE];
	char telefono [TELEFONO_SIZE];
} mensaje;

#endif /* MENSAJES_H_ */
