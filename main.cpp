#include <iostream>
#include <system_error>
# include <sstream>
# include <unistd.h>
# include "Servidor.h"
# include <stdlib.h>
# include  <sys/wait.h>
# include "Cliente.h"
# include "Mensajes.h"

int main(int argc, char* argv[]) {
    try {
        std::cout << "== Gestor de base de Datos  ==" << std::endl;
        int cantDeClientes = (argc > 1) ? atoi(argv[1]) : 2;

        static const int NROPROCESSREQUEST = 3;
        std::cout << "Cantidad de clientes: " << cantDeClientes << std::endl;
        int processId = fork();

        if (processId == 0) {  //Hijo
            //Creo servidor

            Servidor servidor("/bin/cat", 'a');
            std::cout << "\n Se creo el proceso servidor con ProcessId : " << getpid() <<std::endl;
            for (int i = 0; i < NROPROCESSREQUEST; i++) {
                std::cout << "\n Servidor : esperando peticiones " << std::endl;
                //Lee de la cola
                servidor.recibirPeticion();

                std::cout << "\n Servidor : peticion recibida : " << servidor.getPeticionRecibida().estadoDeTransaccion
                          << std::endl;

                servidor.procesarPeticion();
                std::cout << " Servidor : peticion procesada - enviando respuesta : "
                          << servidor.getRespuesta().estadoDeTransaccion << std::endl;
                //Escribe en la cola
                servidor.responderPeticion();
                std::cout << " Servidor : respuesta enviada " << std::endl;
            }

        return 0;
    } else {
             // cliente
             Cliente cliente("/bin/cat", 'a');
             for (int i = 0; i < NROPROCESSREQUEST; i++) {
             std::cin.get();
             // se arma el texto del mensaje
             std::stringstream peticion;
             peticion << " Peticion " << (i + 1) << " del cliente ";
             // se envia el mensaje al servidor
             mensaje rta = cliente.enviarPeticion(i + 1, peticion.str());
             std::cout << " Cliente : respuesta recibida = ( ID = " << rta.id << " ) - " << rta.estadoDeTransaccion << std::endl;
             }//Fin for
             wait(NULL);

            std::cout << "\n== Fin de las transacciones ==" << std::endl;
             return 0;
           }

    }//Fin try
    catch (const std::system_error &e) {
        std::cout << "*\n** Error: " << e.code() << " -> " << e.what() << std::endl;
        return -1;
        }

}//Fin del main()