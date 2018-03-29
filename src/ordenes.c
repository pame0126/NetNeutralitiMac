
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "cliente.h"
#include "hamburgesa.h"
#include "ordenes.h"


int main(int argc, char **argv)
{
	int opcion;
	char *mensaje = (char*)calloc(PACKAGESIZE,sizeof(char));
	char*ip = (char*)calloc(11, sizeof(char));
	char*puerto = (char*)calloc(5, sizeof(char));
	char*prioridad = (char*)calloc(6, sizeof(char));
	
	int procesos = 0;
	
	//si es una prueba de stress
	if( (strcmp(argv[0], "./stress") == 0) && 
		(strcmp(argv[1], "-n")       == 0)){
		procesos = atoi(argv[2]);
	}
	
	//se procesa como una orden de cliente normal
	while((opcion = getopt(argc,argv,"n:h:c:p:hcp")) != -1)
	{
		switch (opcion)
		{
			case 'n':
				break;
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
	
	//se enviara 1 vez si es cliente, si es de Stress sera n veces indicado.
	if(strcmp(argv[0],"./client")==0){
		inicializar_cliente(puerto, ip);
		envia_orden(mensaje);
		cerrar_cliente();
	}
	else{
		for(int i = 0;i < procesos;i++){
			inicializar_cliente(puerto, ip);
			envia_orden(mensaje);
			cerrar_cliente();
		}	
		//COCINAR|PRIORIDAD
		
	}
	
	//sleep(5);
	
	free(ip);
	free(puerto);
	free(prioridad);
	free(mensaje);
	
	return 0;
}

void call_client(int argc, char**argv){
	main(argc,argv);
}
