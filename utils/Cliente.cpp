#include "Cliente.h"


Cliente :: Cliente ( const std::string& archivo, const char letra ) : m_clienteID(getpid()) {
	this->cola = new Cola<mensaje> ( archivo,letra );
}

Cliente :: ~Cliente() {
	delete this->cola;
}


//Recibe el id de la cola y el mensaje a enviar
mensaje Cliente :: enviarPeticion(const int id) {
	mensaje peticion;
	peticion.id = id;
	peticion.mtype = 1;
	peticion.tipo_operacion = PETICION;
	peticion.remitente = this->m_clienteID;

	this->cola->escribir ( peticion );

	mensaje respuesta;
	this->cola->leer (this->m_clienteID, &respuesta );

	return respuesta;
}

mensaje Cliente::enviarAlta(std::string nombre, std::string direccion, std::string telefono ) {
	mensaje alta;
	alta.id = 0;
	alta.mtype = 1;
	alta.remitente = this->m_clienteID;
	alta.tipo_operacion = ALTA;

	//Copia el texto en la transaccion(mensaje)
	strcpy(alta.estadoDeTransaccion, "alta");
	strcpy(alta.nombre, nombre.c_str() );
	strcpy(alta.direccion, direccion.c_str() );
	strcpy(alta.telefono, telefono.c_str() );

	//Escribe en cola
	this->cola->escribir ( alta );

//	sleep(10);

	mensaje respuesta;
	this->cola->leer (this->m_clienteID,  &respuesta );

	return respuesta;
}
