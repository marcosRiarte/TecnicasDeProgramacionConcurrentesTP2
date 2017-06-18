
#La lista de clases en el directorio actual
set ( SRCS
	Utils.cpp
	Cliente.cpp
	Mensajes.h
	Cola.h
	Servidor.cpp
    )

#Compila la libreria
add_library ( utils ${SRCS} )
