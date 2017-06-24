#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <string.h>

#include <string>
#include <fstream>
#include <vector>

#include "Mensajes.h"
#include "Cola.h"


class Servidor {

	private:
		Cola<mensaje>* cola;

		std::fstream m_db;
		std::vector<std::string> m_cache;

		int m_destinatario;
		int m_ultimaOperacion;
		std::string m_resultadoConsulta;

		int guardar(mensaje reg);
		int consultar(unsigned id);
		void initDB(std::string nomArch);

	public:
		Servidor ( const std::string& archivo, const char letra );
		~Servidor ();

		// Lee de la cola y escribe en la "DB", devuelde el id del registro
		int recibirPeticion ();
		int responderPeticion ();
};

#endif /* SERVIDOR_H_ */
