#include <iostream>
#include <system_error>
#include <sstream>
#include <string>

#include "Cliente.h"
#include "Mensajes.h"


int main() {
    try {
	std::cout << "== Gestor de base de Datos - cliente  ==\n" << std::endl;

	Cliente cliente("/bin/cat", 'a');
	bool keepGoing = true;

	while (keepGoing) {
		std::cout << "A - Alta" << std::endl;
		std::cout << "C - Consulta" << std::endl;
		std::cout << "Q - Salir" << std::endl;
		std::cout << std::endl;

		char op;
		std::cout << "Seleccione la operación: ";
		std::cin >> op;

		if (op == 'A') {
			std::cout << "\nIngrese datos de una nueva persona: " << std::endl;

			std::string nombre;
			std::cout << "Nombre: ";
			std::cin >> nombre;

			std::string direccion;
			std::cout << "Direccion: ";
			std::cin >> direccion;

			std::string telefono;
			std::cout << "Telefono: ";
			std::cin >> telefono;

			mensaje alta = cliente.enviarAlta(nombre, direccion, telefono);
			std::cout << "\nRespuesta recibida: " << alta.estadoDeTransaccion << std::endl;
			std::cout << "\n--------\n" << std::endl;

		} else if (op == 'C') {
			std::cout << "\nIngrese el id de la persona a consultar: " << std::endl;

			int id;
			std::cout << "ID: ";
			std::cin >> id;

			mensaje respuesta = cliente.enviarPeticion(id);
			std::cout << "\nDatos recibidos:\n\t" << respuesta.estadoDeTransaccion << std::endl;
			std::cout << "\n--------\n" << std::endl;

		} else if (op == 'Q') {
			keepGoing = false;
		}
	}

	std::cout << "\n== Cliente cerrado ==" << std::endl;

	return 0;

    } catch (const std::system_error &e) {
        std::cout << "*\n** Error: " << e.code() << " -> " << e.what() << std::endl;
        return 1;
    }
}
