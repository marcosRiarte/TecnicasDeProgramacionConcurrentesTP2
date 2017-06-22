#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <string>
#include <string.h>
#include <sstream>
#include <fstream>

#include "Mensajes.h"
#include "Cola.h"


class Servidor {

	private:
		Cola<mensaje>* cola;
		mensaje peticionRecibida;
		mensaje respuesta;
		std::ofstream my_fileOut;


	public:
		Servidor ( const std::string& archivo,const char letra );
		~Servidor ();

		void crearArchivoAlmacenamiento (std::string fileName);
		int recibirPeticion ();
		int procesarPeticion ();
		int responderPeticion () const;

		mensaje getPeticionRecibida ();
		mensaje getRespuesta ();

};

#endif /* SERVIDOR_H_ */
