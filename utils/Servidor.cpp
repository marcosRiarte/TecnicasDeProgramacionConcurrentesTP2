#include "Servidor.h"


Servidor::Servidor(const std::string& archivo, const char letra)
	: m_db("almacen.txt"), m_destinatario(0), m_ultimaOperacion(0)
{
	this->cola = new Cola<mensaje> ( archivo,letra );
	initDB("almacen.txt");
}


Servidor::~Servidor() {
	this->cola->destruir();
	delete this->cola;

	this->m_db.close();
}

void Servidor::initDB(std::string nomArch) {
	if (!this->m_db) {
		// No se pudo abrir el archivo, lo creo vacio
		this->m_db.open(nomArch, std::ios::trunc | std::ios::in | std::ios::out);

	} else {
		// Se lee el archivo a memoria
		std::string line;
		while (std::getline(this->m_db, line)) {
			this->m_cache.push_back(line);
		}
		this->m_db.clear();
	}
}


int Servidor :: recibirPeticion () {
	mensaje peticionRecibida;
	peticionRecibida.tipo_operacion = -1;

	this->cola->leer(SERVER_ID, &peticionRecibida);

	this->m_destinatario = peticionRecibida.remitente;
	this->m_ultimaOperacion = peticionRecibida.tipo_operacion;

	switch (peticionRecibida.tipo_operacion) {
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
	respuesta.id = 0;
	respuesta.mtype = this->m_destinatario;
	respuesta.remitente = SERVER_ID;
	respuesta.tipo_operacion = RESPUESTA;
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


int Servidor::consultar(unsigned id) {
	if (id <= this->m_cache.size()) {
		this->m_resultadoConsulta = this->m_cache[id-1];
		return 0;
	}

	this->m_resultadoConsulta = "El registro no existe";
	return 1;
}

