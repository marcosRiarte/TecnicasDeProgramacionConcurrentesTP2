#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <unistd.h>
#include <string.h>

#include <string>

#include "Mensajes.h"
#include "Cola.h"


class Cliente {

	private:
		int m_clienteID;
		Cola<mensaje>* cola;

	public:
		Cliente ( const std::string& archivo,const char letra );
		~Cliente();

		mensaje enviarPeticion(const int id);
		mensaje enviarAlta(std::string nombre, std::string direccion, std::string telefono);
};

#endif /* CLIENTE_H_ */
