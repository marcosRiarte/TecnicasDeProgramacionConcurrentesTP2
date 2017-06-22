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
		mensaje enviarAlta (const int id,const std::string& nombre,const std::string& direccion,const std::string& telefono) const;
};

#endif /* CLIENTE_H_ */
