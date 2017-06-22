#include <iostream>
#include <system_error>
#include <sstream>
#include <string>

#include "Cliente.h"
#include "Mensajes.h"


int main(int argc, char* argv[]) {
    try {
	std::cout << "== Gestor de base de Datos - cliente  ==\n" << std::endl;

	Cliente cliente("/bin/cat", 'a');
	bool keepGoing = true;

	while (keepGoing) {
		std::cout << "A - Alta" << std::endl;
		std::cout << "B - Baja (WIP)" << std::endl;
		std::cout << "C - Consulta (WIP)" << std::endl;
		std::cout << "Q - Salir" << std::endl;
		std::cout << std::endl;

		char op;
		std::cout << "Seleccione la operación: ";
		std::cin >> op;

		if (op == 'A') {
			std::cout << "Se envia un alta al servidor" << std::endl;
			mensaje alta = cliente.enviarAlta(1, "Marcos Riarte", "Paseo Colon 850", "1126329053");
			std::cout << "Respuesta recibida: ID = " << alta.id << " - " << alta.estadoDeTransaccion << std::endl;

		} else if (op == 'B' || op == 'C') {
			std::cout << "Work in progress" << std::endl;

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
