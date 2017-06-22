
#La lista de clases en el directorio actual
set ( SRCS
	Utils.cpp
	Cliente.cpp
	Mensajes.h
	Cola.h
	Servidor.cpp
	SignalHandler.cpp
	EventHandler.h
	ExitHandler.h
    )

#Compila la libreria
add_library ( utils ${SRCS} )
