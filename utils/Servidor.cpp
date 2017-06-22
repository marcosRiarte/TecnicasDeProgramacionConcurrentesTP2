#include "Servidor.h"


Servidor :: Servidor ( const std::string& archivo,const char letra ) {
	this->cola = new Cola<mensaje> ( archivo,letra );
	this->m_db.open("almacen.txt", std::ios::trunc | std::ios::in | std::ios::out);
}


Servidor :: ~Servidor () {
	this->cola->destruir ();
	delete this->cola;
	this->m_db.close();
}


int Servidor :: recibirPeticion () {
	mensaje peticionRecibida;
	int res = this->cola->leer(PETICION, &peticionRecibida);
	if (res == -1) {	// Recibio la señal de salida
		return 0;
	}

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

