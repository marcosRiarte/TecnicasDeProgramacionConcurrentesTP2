
#La lista de clases en el directorio actual
set ( SRCS
	Utils.cpp
	Cliente.cpp
	Servidor.cpp
	SignalHandler.cpp
    )

#Compila la libreria
add_library ( utils ${SRCS} )
