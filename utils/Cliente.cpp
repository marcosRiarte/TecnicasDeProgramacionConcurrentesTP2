#include "Cliente.h"


Cliente :: Cliente ( const std::string& archivo,const char letra ) {
	this->cola = new Cola<mensaje> ( archivo,letra );
}

Cliente :: ~Cliente() {
	delete this->cola;
}


//Recibe el id de la cola y el mensaje a enviar
mensaje Cliente :: enviarPeticion(const int id) {
	mensaje peticion;
	peticion.mtype = PETICION;
	peticion.id = id;

	this->cola->escribir ( peticion );

	mensaje respuesta;
	this->cola->leer ( &respuesta );

	return respuesta;
}

mensaje Cliente::enviarAlta(std::string nombre, std::string direccion, std::string telefono ) {
	mensaje alta;
	alta.mtype = ALTA;
	alta.id = 0;

	//Copia el texto en la transaccion(mensaje)
	strcpy(alta.estadoDeTransaccion, "alta");
	strcpy(alta.nombre, nombre.c_str() );
	strcpy(alta.direccion, direccion.c_str() );
	strcpy(alta.telefono, telefono.c_str() );

	//Escribe en cola
	this->cola->escribir ( alta );

	mensaje respuesta;
	this->cola->leer ( &respuesta );

	return respuesta;
}
