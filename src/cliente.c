/*
 * Modelo ejemplo de un Cliente que envia mensajes a un Server.
 *
 * 	No se contemplan el manejo de errores en el sistema por una cuestion didactica. Tener en cuenta esto al desarrollar.
 */

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


	//int serverSocket;
	//se usa global del secket cliente
	serverSocketCliente = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

	connect(serverSocketCliente, serverInfo->ai_addr, serverInfo->ai_addrlen);
	freeaddrinfo(serverInfo);	// No lo necesitamos mas


	//int enviar = 1;
	//char message[PACKAGESIZE];

	//printf("Conectado al servidor. Bienvenido al sistema, ya puede enviar mensajes. Escriba 'exit' para salir\n");
	
	//while(enviar){
		//fgets(message, PACKAGESIZE, stdin);			// Lee una linea en el stdin (lo que escribimos en la consola) hasta encontrar un \n (y lo incluye) o llegar a PACKAGESIZE.
		//if (!strcmp(message,"exit\n")) enviar = 0;			// Chequeo que el usuario no quiera salir
		/**if (strlen(message) < PACKAGESIZE){
			 
			 send(serverSocketCliente, message, strlen(message) + 1, 0); 	// Solo envio si el usuario no quiere salir.
		 }*/
//	}

	//close(serverSocketCliente);

	/* ADIO'! */
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
