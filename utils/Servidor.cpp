#include "Servidor.h"


Servidor :: Servidor ( const std::string& archivo,const char letra ) : m_ultimaOperacion(0) {
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
	this->cola->leer(&peticionRecibida);
	this->m_ultimaOperacion = peticionRecibida.mtype;

	switch (peticionRecibida.mtype) {
		case ALTA:
			return guardar(peticionRecibida);

		case PETICION:
			return consultar(peticionRecibida.id);

		default:
			// Indefinida, tambien entra acá si recibio la señal de salida
			break;
	}

	return 0;
}


int Servidor :: responderPeticion() {
	std::string textoRta = "";
	switch (this->m_ultimaOperacion) {
		case ALTA:
			textoRta = "[ Registro guardado con ID: " 
				+ std::to_string(this->m_cache.size()) + " ]";
			break;

		case PETICION:
			textoRta = this->m_resultadoConsulta;
			break;

		default:
			textoRta = "no-op";
			break;
	}

	mensaje respuesta;
	respuesta.mtype = RESPUESTA;
	respuesta.id = 0;
	strcpy(respuesta.estadoDeTransaccion, textoRta.c_str());

	this->cola->escribir(respuesta);

	return 0;
}


int Servidor::guardar(mensaje regAlta) {
	// Guarda el registro en el cache y en el archivo 
	int id = this->m_cache.size() +1;
	std::string reg = std::to_string(id)
		+ " | " + regAlta.nombre 
		+ " | " + regAlta.direccion 
		+ " | " + regAlta.telefono;

	this->m_cache.push_back(reg);
	this->m_db << reg << std::endl;

	return id;
}


int Servidor::consultar(int id) {
	if (id > 0 && id <= this->m_cache.size()) {
		this->m_resultadoConsulta = this->m_cache[id-1];
		return 0;
	}

	this->m_resultadoConsulta = "El registro no existe";
	return 1;
}

