#ifndef COLA_H_
#define COLA_H_

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string>

#include "Utils.h"


template <class T> class Cola {
	private:
		key_t	clave;
		int	id;

	public:
		Cola ( const std::string& archivo,const char letra );
		virtual ~Cola() = default;

		int escribir ( const T& dato ) const;
		int leer ( const int tipo,T* buffer ) const;
		int destruir () const;
};


template <class T> Cola<T> :: Cola ( const std::string& archivo,const char letra ) {
	this->clave = ftok ( archivo.c_str(),letra );
	utils::checkError(this->clave, "Error en ftok al crear la clave de la cola");

	//Devuelve  el id de la cola
	this->id = msgget ( this->clave,0777|IPC_CREAT );
	utils::checkError(this->id, "Error en msgget");
}


template <class T> int Cola<T> :: destruir () const {
	int resultado = msgctl ( this->id,IPC_RMID,NULL );
	utils::checkError(resultado, "No se pudo destruir la cola");
	return resultado;
}


//Escribe en la cola con el id un mesaje y dvuelve 0 si se produjo con exito
template <class T> int Cola<T> :: escribir ( const T& dato ) const {
	int resultado = msgsnd ( this->id,static_cast<const void*>(&dato),sizeof(T)-sizeof(long),0 );
	utils::checkErrorWithInteruption(resultado, "No se pudo escribir  en la cola");
	return resultado;
}

//Lee en cola:Devuelve la cantidad de byte copiados en el buffer sin contar el long inicial
template <class T> int Cola<T> :: leer ( const int tipo,T* buffer ) const {
	int resultado = msgrcv ( this->id,static_cast<void *>(buffer),sizeof(T)-sizeof(long),tipo,0 );
	utils::checkErrorWithInteruption(resultado, "No se pudo leer de la cola");
	return resultado;
}

#endif /* COLA_H_ */
