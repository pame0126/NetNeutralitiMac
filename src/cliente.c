
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "cliente.h"

int serverSocketCliente;


void inicializar_cliente(char*puerto, char*ip){
	
	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		// Permite que la maquina se encargue de verificar si usamos IPv4 o IPv6
	hints.ai_socktype = SOCK_STREAM;	// Indica que usaremos el protocolo TCP

	getaddrinfo(ip, puerto, &hints, &serverInfo);	// Carga en serverInfo los datos de la conexion

	//se usa global del socket cliente
	serverSocketCliente = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

	connect(serverSocketCliente, serverInfo->ai_addr, serverInfo->ai_addrlen);
	freeaddrinfo(serverInfo);	// No lo necesitamos mas

}

void envia_orden(char*msj)
{
	if (strlen(msj) < PACKAGESIZE){
			 
			 send(serverSocketCliente, msj, strlen(msj) + 1, 0); 	// Solo envio si el usuario no quiere salir.
		 }
}

void cerrar_cliente()
{
	close(serverSocketCliente);
}
