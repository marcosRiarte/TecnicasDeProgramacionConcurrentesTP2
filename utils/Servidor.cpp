#include "Servidor.h"


Servidor :: Servidor ( const std::string& archivo,const char letra ) {
	this->cola = new Cola<mensaje> ( archivo,letra );
	this->crearArchivoAlmacenamiento("almacenamiento.txt");
}


void Servidor::crearArchivoAlmacenamiento (std::string fileName) {
	this->m_db.open(fileName);

	// Leo todo el archivo en nuestro cache
	std::string line;
	while (std::getline(this->m_db, line)) {
		this->m_cache.push_back(line);
	}
}

Servidor :: ~Servidor () {
	this->cola->destruir ();
	delete this->cola;
	this->m_db.close();
}


int Servidor :: recibirPeticion () {
	mensaje peticionRecibida;
	this->cola->leer(PETICION, &peticionRecibida);

	// Guarda el registro en el cache y en el archivo 
	int id = this->m_cache.size() +1;
	std::string reg = std::to_string(id)
		+ " | " + peticionRecibida.nombre 
		+ " | " + peticionRecibida.direccion 
		+ " | " + peticionRecibida.telefono;

	this->m_cache.push_back(reg);
	this->m_db << reg << std::endl;

	return id;
}

int Servidor :: responderPeticion() {
	std::string textoRta = "[ Registro guardado con ID: " 
		+ std::to_string(this->m_cache.size()) 
		+ " ]";

	mensaje respuesta;
	respuesta.mtype = RESPUESTA;
	respuesta.id = this->m_cache.size();
	strcpy(respuesta.estadoDeTransaccion, textoRta.c_str());

	this->cola->escribir(respuesta);

	return 0;
}

