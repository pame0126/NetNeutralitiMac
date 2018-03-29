
#include <stdio.h>
#include <unistd.h>
#include "hamburgesa.h"
#include "archivos.h"

/**Cocinar hamburgesa alta
 * Cocinar rapido
 * */
void cocinar_hamburgesa_alta()
{
	printf("Cocinando hamburgesa..... \t(Priori ALTO)\n");
	escribir_fichero("Cocinando hamburgesa.....            (Priori ALTO)");
	sleep(RAPIDO);   
	escribir_fichero("Listo!!!....");
	printf("Listo!!!....\n");
}


/**Cocinar hamburgesa media
 * Cocinar regular
 * */
void cocinar_hamburgesa_media()
{
	printf("Cocinando hamburgesa..... \t(Priori MEDIO)\n");
	escribir_fichero("Cocinando hamburgesa.....            (Priori MEDIO)");
	sleep(REGULAR); 
	escribir_fichero("Listo!!!....");
	printf("Listo!!!....\n");
}


/**Cocinar hamburgesa media
 * Cocinar regular
 * */
void cocinar_hamburgesa_baja()
{
	printf("Cocinando hamburgesa..... \t(Priori BAJO)\n");
	escribir_fichero("Cocinando hamburgesa.....            (Priori BAJO)");
	sleep(LENTO);   
	escribir_fichero("Listo!!!....");
	printf("Listo!!!....\n");
}
