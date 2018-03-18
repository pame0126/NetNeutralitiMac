#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "hamburgesa.h"
#include "servidorPrethread.h"
#include "thpool.h"


#define PUERTO "6667"
#define BACKLOG 5			// Define cuantas conexiones vamos a mantener pendientes al mismo tiempo
#define PACKAGESIZE 1024	// Define cual va a ser el size maximo del paquete a enviar


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
	
	token = strtok(msj, "|");
	strcpy(accion, token);
	accion = toUpCharString(accion);
	
	msj = msj + (strlen(token)+1);
	strcpy(priori, msj);
	priori = toUpCharString(priori);
}

void asignar_hilo_a_hamburgesa(char*priori, threadpool hilos)
{
	if(strcmp(priori, ALTA) == 0)
	{
		thpool_add_work(hilos, (void*)cocinar_hamburgesa_alta, NULL);
		thpool_resume(hilos);
	}
	else if(strcmp(priori, MEDIA) == 0)
	{
		thpool_add_work(hilos, (void*)cocinar_hamburgesa_media, NULL);
		thpool_resume(hilos);
	}
	else if(strcmp(priori, BAJA) == 0)
	{
		thpool_add_work(hilos, (void*)cocinar_hamburgesa_baja, NULL);
		thpool_resume(hilos);
	}
	else
	{
		printf("ERROR: No es una configuración valida.\n Debe ser ALTA  MEDIA  BAJA\n");
		printf("%s\n", priori);
		printf("Hilos activos %d\n",thpool_num_threads_working(hilos));
	}
}

/**
 * Inicia el servidor cargado con hilos no activos
 * */
void inicializar_servidor_prethreads(int cant_hilos, char*prioridad_serv, char*recursos, char*puerto)
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

	//Espera conexion con el cliente
	int socketCliente = accept(listenningSocket, (struct sockaddr *) &addr, &addrlen);
	
	//aqui van los hilos
	threadpool hilos = thpool_init(cant_hilos);

	/* Preparando para escuchar al cliente */

	char msj[PACKAGESIZE];
	int status = 1;		// Estructura que manjea el status de los recieve.

	printf("Cliente conectado. Esperando mensajes:\n");
	
	char*accion;
	char* priori;
	char* cant_h;
	
	int bandera = 1;
	
	while (bandera){
		status = recv(socketCliente, (void*) msj, PACKAGESIZE, 0);
		
		if (status != 0)//Leyendo mensajes
		{
			accion = (char*)calloc(10, sizeof(char));
			priori = (char*)calloc(10, sizeof(char));
			cant_h = (char*)calloc(6, sizeof(char));
			
			procesar_mensaje(msj, accion, priori);
			
			if(strcmp(priori,SALIR) == 0)
			{
				bandera = 0;
			}
			if(strcmp(accion,COCINAR) == 0)//si es el mensaje COCINA
			{
				asignar_hilo_a_hamburgesa(priori,hilos);
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
	thpool_destroy(hilos);
}


int main(int argc, char **argv)
{
	/* Leer entrada */
	
	int opcion;
	int cant_hilos = 0;
	char*priori_serv = (char*)calloc(10, sizeof(char));
	char*recursos = (char*)calloc(100, sizeof(char));
	char*puerto = (char*)calloc(5, sizeof(char));
	
	while((opcion = getopt(argc,argv,"n:P:r:p")) != -1)
	{
		
		switch (opcion)
		{
			case 'n'://cantidad de hilos
				cant_hilos = atoi(optarg);
				break;
				
			case 'P'://Prioridad del servidor
				strcpy(priori_serv,optarg);
				priori_serv = toUpCharString(priori_serv);
				break;
				
			case 'r'://Recursos, carpeta de imagenes
				strcpy(recursos,optarg);
				break;
				
			case 'p'://puerto
			/*  Falla la lectura del puerto -> NULL
				//strcpy(puerto,optarg);
				printf("%s\n", optarg);
				//printf("%d %s %s  %s\n", cant_hilos, priori_serv, recursos, puerto);
			*/
				break;
				
			default:
				printf("ERROR: No son opciones validas\n");
				break;
		}
	}
	//iniciar el servidor de prethreads
	inicializar_servidor_prethreads(cant_hilos, priori_serv, recursos, "6667");
	
	
	/* Liberar espacios */
	free(priori_serv);
	free(recursos);
	free(puerto);
	return 0;
}
