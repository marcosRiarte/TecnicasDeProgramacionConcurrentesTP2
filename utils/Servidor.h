#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <string.h>

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "Mensajes.h"
#include "Cola.h"


class Servidor {

	private:
		Cola<mensaje>* cola;

		std::fstream m_db;
		std::vector<std::string> m_cache;

		void crearArchivoAlmacenamiento (std::string fileName);

	public:
		Servidor ( const std::string& archivo,const char letra );
		~Servidor ();

		// Lee de la cola y escribe en la "DB", devuelde el id del registro
		int recibirPeticion ();
		int responderPeticion ();
};

#endif /* SERVIDOR_H_ */
