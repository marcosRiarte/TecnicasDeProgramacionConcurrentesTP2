#include "Cliente.h"

Cliente :: Cliente ( const std::string& archivo,const char letra ) {
	this->cola = new Cola<mensaje> ( archivo,letra );
}

Cliente :: ~Cliente() {
	this->cola->destruir ();
	delete this->cola;
}


//Recibe el id de la cola y el mensaje a enviar
mensaje Cliente :: enviarPeticion ( const int id,const std::string& texto ) const {
	mensaje peticion;
	mensaje respuesta;

	peticion.mtype = PETICION;
	peticion.id = id;
	//Todo  for me : refactoriza resolviendo problema mesaje
    //Copia el texto en la transaccion(mensaje)
	strcpy ( peticion.estadoDeTransaccion,texto.c_str() );
    //Escribe en cola y luego lee
	this->cola->escribir ( peticion );
	this->cola->leer ( RESPUESTA,&respuesta );

	return respuesta;
}

mensaje Cliente::enviarAlta (const int id,const std::string& nombre,const std::string& direccion,const std::string& telefono ) const {
	mensaje alta;
	alta.mtype = PETICION;
	alta.id = id;

	//Copia el texto en la transaccion(mensaje)
	const std::string texto =" Peticion " + std::to_string(id) + " del cliente ";
	strcpy(alta.estadoDeTransaccion, texto.c_str());
	strcpy(alta.nombre, nombre.c_str() );
	strcpy(alta.direccion, direccion.c_str() );
	strcpy(alta.telefono, telefono.c_str() );

	//Escribe en cola
	this->cola->escribir ( alta );

	mensaje respuesta;
	this->cola->leer ( RESPUESTA,&respuesta );

	return respuesta;
}
