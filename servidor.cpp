#include <iostream>
#include <system_error>

#include "Servidor.h"
#include "ExitHandler.h"
#include "SignalHandler.h"


int main(int argc, char* argv[]) {
    try {
        std::cout << "== Gestor de base de Datos - Servidor  ==" << std::endl;
        std::cout << "Ctrl-C para salir\n" << std::endl;

	// Creo servidor
	Servidor servidor("/bin/cat", 'a');


	// Controla cuando llega la señal para salir
	utils::ExitHandler exitHandler;
	utils::SignalHandler* sigHandler = utils::SignalHandler::getInstance();
	sigHandler->registrarHandler(utils::ExitHandler::SIG_EXIT, &exitHandler);

	while (!exitHandler.exitRecibido) {
		// Lee de la cola y queda a la espera de que haya datos.
		std::cout << "Esperando... ";
		servidor.recibirPeticion();
		std::cout << "recibido" << std::endl;

		// Escribre la respuesta en el mensaje
		std::cout << "Enviando ACK... ";
		servidor.responderPeticion();
		std::cout << "enviado." << std::endl;
	}

	// Destruye el manejador de señales
	sigHandler->removerHandler(utils::ExitHandler::SIG_EXIT);
	utils::SignalHandler::destruir();
	sigHandler = nullptr;

        std::cout << "== Servidor apagado  ==" << std::endl;

	return 0;

    } catch (const std::system_error &e) {
        std::cout << "*\n** Error: " << e.code() << " -> " << e.what() << std::endl;
        return 1;
    }
}
