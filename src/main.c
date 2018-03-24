
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "cliente.h"
#include "hamburgesa.h"



int main(int argc, char **argv)
{
	int opcion;
	char *mensaje = (char*)calloc(PACKAGESIZE,sizeof(char));
	char*ip = (char*)calloc(11, sizeof(char));
	char*puerto = (char*)calloc(5, sizeof(char));
	char*prioridad = (char*)calloc(6, sizeof(char));
	
	
	while((opcion = getopt(argc,argv,"h:c:p:hcp")) != -1)
	{
		
		switch (opcion)
		{
			case 'h'://IP
				strcpy(ip, optarg);
				break;
				
			case 'p':
				strcpy(puerto, optarg);
				break;
				
			case 'c'://configuracion de orden, alta, media o baja
				strcat(prioridad,optarg);
				break;
				
			default:
				printf("ERROR: No son opciones validas\n");
				break;
		}
	}
	
	strcpy(mensaje,COCINAR);
	strcat(mensaje,"|");
	strcat(mensaje,prioridad);
	
	inicializar_cliente(puerto, ip);
	
	//COCINAR|PRIORIDAD
	envia_orden(mensaje);
	//sleep(5);
	cerrar_cliente();
	free(ip);
	free(puerto);
	free(prioridad);
	free(mensaje);
	
	return 0;
}

