/*Clase servidor */
#include "Servidor.h"


Servidor :: Servidor ( const std::string& archivo,const char letra ) {
	this->cola = new Cola<mensaje> ( archivo,letra );
	this->crearArchivoAlmacenamiento("almacenamiento.txt");
}

//Crea archivo de almacenamiento
void Servidor::crearArchivoAlmacenamiento (std::string fileName) {
            this->my_fileOut.open(fileName, std::ios_base::trunc);
}

Servidor :: ~Servidor () {
	this->cola->destruir ();
	delete this->cola;
}

//LEE COLA
int Servidor :: recibirPeticion () {
	this->peticionRecibida.id = 0;
	this->cola->leer ( PETICION,&(this->peticionRecibida) );

	//TODO PROBANDO LA TRANSACCION //POSIBLE LOCK
	this->my_fileOut << this->peticionRecibida.id << std::endl;
	this->my_fileOut << this->peticionRecibida.nombre << std::endl;
	this->my_fileOut << this->peticionRecibida.direccion << std::endl;
	this->my_fileOut << this->peticionRecibida.telefono << std::endl;

	return 0;
}

int Servidor :: procesarPeticion () {
	std::stringstream textoRta;
	//TODO FOR ME refactorizar "MENSAJE"
	textoRta << "[Respuesta a " << this->peticionRecibida.estadoDeTransaccion << "]";

	this->respuesta.mtype = RESPUESTA;
	this->respuesta.id = this->peticionRecibida.id;
	//TODO REFACTORIZAR "MENSAJE"
	strcpy ( this->respuesta.estadoDeTransaccion,textoRta.str().c_str() );

	return 0;
}

int Servidor :: responderPeticion () const {
	this->cola->escribir ( this->respuesta );
	return 0;
}

mensaje Servidor :: getPeticionRecibida () {
	return this->peticionRecibida;
}

mensaje Servidor :: getRespuesta () {
	return this->respuesta;
}

