
#include <stdio.h>
#include <unistd.h>
#include "hamburgesa.h"

/**Cocinar hamburgesa alta
 * Cocinar rapido
 * */
void cocinar_hamburgesa_alta()
{
	printf("Cocinando hamburgesa..... \t(Priori ALTO)\n");
	sleep(RAPIDO);   
	printf("Listo!!!....\n");
}


/**Cocinar hamburgesa media
 * Cocinar regular
 * */
void cocinar_hamburgesa_media()
{
	printf("Cocinando hamburgesa..... \t(Priori MEDIO)\n");
	sleep(REGULAR); 
	printf("Listo!!!....\n");
}


/**Cocinar hamburgesa media
 * Cocinar regular
 * */
void cocinar_hamburgesa_baja()
{
	printf("Cocinando hamburgesa..... \t(Priori BAJO)\n");
	sleep(LENTO);   
	printf("Listo!!!....\n");
}
