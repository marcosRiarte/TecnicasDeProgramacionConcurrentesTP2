#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <system_error>
#include <sstream>
#include "Servidor.h"
#include "Cliente.h"
#include "Mensajes.h"

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
            std::cout << "\n Se creo el proceso SERVIDOR con ProcessId : " << getpid() <<std::endl;
            for (int i = 0; i < NROPROCESSREQUEST; i++) {
                std::cout << "\n Servidor : esperando peticiones " << std::endl;
                //Lee de la cola y queda a la espera de que haya datos.
                servidor.recibirPeticion();

                //Devolvera el mensaje enviado por el cliente
                std::cout << "\n Servidor : peticion recibida : " << servidor.getPeticionRecibida().estadoDeTransaccion
                          << std::endl;
                //Prepara la respuesta
                servidor.procesarPeticion();
                //Escribre la respuesta en el mensaje
                std::cout << " Servidor : peticion procesada - enviando respuesta : "
                          << servidor.getRespuesta().estadoDeTransaccion << std::endl;
                //Escribe en la cola en mensaje de respuesta.
                servidor.responderPeticion();
                std::cout << " Servidor : respuesta enviada " << std::endl;
            }

        return 0;
    } else {
             // cliente
             Cliente cliente("/bin/cat", 'a');
             std::cout << "\n Se creo el proceso CLIENTE con ProcessId : " << getpid() <<std::endl;

             for (int i = 0; i < NROPROCESSREQUEST; i++) {
             std::cin.get();

             // se arma el texto del mensaje
             std::stringstream peticion;
             peticion << " Peticion " << (i + 1) << " del cliente ";

             // se envia el mensaje al servidor (escribe en la cola) y recibe el mensaje de respuesta (lee cola)
             //mensaje rta = cliente.enviarPeticion(i + 1, peticion.str());
             //std::cout << " Cliente : respuesta recibida = ( ID = " << rta.id << " ) - " << rta.estadoDeTransaccion << std::endl;
             //-----Alta
             std::cout << " Alta numero " << (i + 1) << " del cliente "<< getpid() << std::endl;
             mensaje alta = cliente.enviarAlta(i + 1,"Marcos Riarte","Paseo Colon 850","1126329053");
             std::cout << " Cliente : respuesta de alta recibida = ( ID = " << alta.id << " ) - " << alta.estadoDeTransaccion << std::endl;
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
