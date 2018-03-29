#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "archivos.h"

enum {EXITO, FALLO, LONGITUD_MAXIMA=5000 };

char*leer_fichero(){
	FILE *fd;
	int c;
	char dir[]="hamb_mc.txt";
	char*buffer = calloc(LONGITUD_MAXIMA, sizeof(char));
	fd = fopen(dir, "rt");
	
	while(fd == NULL){
		fd = fopen(dir, "rt");
	}
	int i = 0;
	while((c=fgetc(fd)) != EOF){
		buffer[i] = c;
		i++;
	}
	buffer[i] = '\0';
	fclose(fd);
  return buffer;
}
void escribir_fichero(char*msj){
	//char*buffer = leer_fichero();
	
	FILE *fd;
	int c;
	char dir[]="hamb_mc.txt";
	fd = fopen(dir, "a");
	
	while(fd == NULL){
		fd = fopen(dir, "a");
	}
	int i = 0;
	fprintf(fd, "%c%s",'\n', msj);
	fclose(fd);
}


