#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <errno.h>
#include <sys/wait.h>

#include "hamburgesa.h"

#define PUERTO "6667"
#define BACKLOG 5			// Define cuantas conexiones vamos a mantener pendientes al mismo tiempo
#define PACKAGESIZE 1024	// Define cual va a ser el size maximo del paquete a enviar



void init_forks(int cant)
{
	pid_t pid;
	int x;

	for(x=1;x<=cant;x++)
	{
		pid=fork(); 
	}
}


void asignar_fork_a_hamburgesa(char*priori)
{
	if(strcmp(priori, ALTA) == 0)
	{
		cocinar_hamburgesa_alta();
		
	}
	else if(strcmp(priori, MEDIA) == 0)
	{
		cocinar_hamburgesa_media();
	}
	else if(strcmp(priori, BAJA) == 0)
	{
		cocinar_hamburgesa_baja();
	}
	else
	{
		printf("ERROR: No es una configuración valida.\n Debe ser ALTA  MEDIA  BAJA\n");
	}
}


char* toUpCharString(char*str)
{
	int i=0;
	while(str[i]!='\0'){
		str[i] = toupper(str[i]);
		i++;
	}
	return str;
}

/**Procesar Mensaje
 * Separa los contenidos del --> char msj
 * en:    char*accion
 *        char* priori
 *        char*cant
 * */
void procesar_mensaje(char*msj, char*accion, char* priori)
{
	char*token;
	//Accion
	token = strtok(msj, "|");
	strcpy(accion, token);
	accion = toUpCharString(accion);
	//Prioridad
	msj = msj + (strlen(token)+1);
	strcpy(priori, msj);
	priori = toUpCharString(priori);
}

/**
 * Inicia el servidor cargado con hilos no activos
 * */
void inicializar_servidor_forks(int cant_forks, char*recursos, char*puerto)
{
	/* Iniciar el servidor */	
	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		// No importa si uso IPv4 o IPv6
	hints.ai_flags = AI_PASSIVE;		// Asigna el address del localhost: 127.0.0.1
	hints.ai_socktype = SOCK_STREAM;	// Indica que usaremos el protocolo TCP

	getaddrinfo(NULL, puerto, &hints, &serverInfo); // Notar que le pasamos NULL como IP, ya que le indicamos que use localhost en AI_PASSIVE
    
	/* Necesitamos un socket que escuche las conecciones entrantes */
	int listenningSocket;
	listenningSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);

	bind(listenningSocket,serverInfo->ai_addr, serverInfo->ai_addrlen);
	freeaddrinfo(serverInfo); // Ya no lo vamos a necesitar

	listen(listenningSocket, BACKLOG);		// IMPORTANTE: listen() es una syscall BLOQUEANTE.

	struct sockaddr_in addr;			// Esta estructura contendra los datos de la conexion del cliente. IP, puerto, etc.
	socklen_t addrlen = sizeof(addr);


	/* Preparando para escuchar al cliente */

	char msj[PACKAGESIZE];
	int status = 1;		// Estructura que manjea el status de los recieve.
	
	char*accion;
	char* priori;
	char* cant_h;
	
	char salir[5];
	
	int bandera = 1;
	int socketCliente;
	//aqui van los forks creados
	init_forks(cant_forks);
	
	while (bandera){
		status = recv(socketCliente, (void*) msj, PACKAGESIZE, 0);
		
		if (status != 0)//Leyendo mensajes
		{
			accion = (char*)calloc(10, sizeof(char));
			priori = (char*)calloc(10, sizeof(char));
			cant_h = (char*)calloc(6, sizeof(char));
			
			procesar_mensaje(msj, accion, priori);
			
			if(strcmp(accion,COCINAR) == 0)//si es el mensaje COCINA
			{
				asignar_fork_a_hamburgesa(priori);
			}
			/*Libera espacios*/
			free(accion);
			free(priori);
			free(cant_h);
		}
		//escucha nuevas conexiones de clientes
		socketCliente = accept(listenningSocket, (struct sockaddr *) &addr, &addrlen);
	}

	close(socketCliente);
	close(listenningSocket);
	/* Cerramos el socket del Cliente y Servidor */
	//thpool_destroy(hilos);
	
}


int main(int argc, char **argv)
{
	/* Leer entrada */
	int opcion;
	int cant_forks = 0;
	char*priori_serv = (char*)calloc(10, sizeof(char));
	char*recursos = (char*)calloc(100, sizeof(char));
	char*puerto = (char*)calloc(5, sizeof(char));

	
	while((opcion = getopt(argc,argv,"n:r:p:nrp")) != -1)
	{
		
		switch (opcion)
		{
			case 'n'://cantidad de hilos
				cant_forks = atoi(optarg);
				break;
			
			case 'r'://Recursos, carpeta de imagenes
				strcpy(recursos,optarg);
				break;
				
			case 'p'://puerto
			strcpy(puerto,optarg);
				break;
				
			default:
				printf("ERROR: No son opciones validas\n");
				break;
		}
	}
	//iniciar el servidor de prethreads
	inicializar_servidor_forks(7, "/home/wifuss/Imágenes/Facebook/hamburgesa_img/", "6667");
	//printf("%d %s %s\n", cant_forks, recursos, puerto);
	
	
	/* Liberar espacios */
	free(priori_serv);
	free(recursos);
	free(puerto);
	return 0;
}
