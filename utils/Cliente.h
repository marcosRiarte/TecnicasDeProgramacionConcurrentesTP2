#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string>
#include <string.h>

#include "Mensajes.h"
#include "Cola.h"

class Cliente {

	private:
		Cola<mensaje>* cola;

	public:
		Cliente ( const std::string& archivo,const char letra );
		~Cliente();
		mensaje enviarPeticion ( const int id,const std::string& texto ) const;
};

#endif /* CLIENTE_H_ */
