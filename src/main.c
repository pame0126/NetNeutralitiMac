
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
	//char*orden = (char*)calloc(10, sizeof(char));
	strcpy(mensaje,COCINAR);
	strcat(mensaje,"|");
	
	while((opcion = getopt(argc,argv,"h:c:hc")) != -1)
	{
		
		switch (opcion)
		{
			case 'h'://IP
				strcpy(ip, optarg);
				break;
				
			case 'c'://configuracion de orden, alta, media o baja
				
				strcat(mensaje,optarg);
				strcat(mensaje, "\0");
				break;
			default:
				printf("ERROR: No son opciones validas\n");
				break;
		}
	}
	
	inicializar_cliente(PUERTO, ip);
	//COCINAR|PRIORIDAD|CANTIDAD
	
	envia_orden(mensaje);
	//sleep(5);
	cerrar_cliente();
	free(ip);
	free(mensaje);
	
	return 0;
}

