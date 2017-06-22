#include <iostream>
#include <system_error>

#include "Servidor.h"


int main(int argc, char* argv[]) {
    try {
        std::cout << "== Gestor de base de Datos - Servidor  ==" << std::endl;

	// Creo servidor
	Servidor servidor("/bin/cat", 'a');
	bool keepGoing = true;

	while (keepGoing) {
		// TODO: Salir/cerrar el servidor

		// Lee de la cola y queda a la espera de que haya datos.
		std::cout << "Esperando... ";
		servidor.recibirPeticion();
		std::cout << "recibido" << std::endl;

		// Prepara la respuesta
		servidor.procesarPeticion();

		// Escribre la respuesta en el mensaje
		std::cout << "Enviando ACK... ";
		servidor.responderPeticion();
		std::cout << "enviado." << std::endl;
	}

        std::cout << "== Servidor apagado  ==" << std::endl;

	return 0;

    } catch (const std::system_error &e) {
        std::cout << "*\n** Error: " << e.code() << " -> " << e.what() << std::endl;
        return 1;
    }
}
