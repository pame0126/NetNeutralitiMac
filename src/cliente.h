
#ifndef CLIENTE_H
#define CLIENTE_H

#define IP "127.0.0.1"
#define PUERTO "6667"
#define PACKAGESIZE 1024	// Define cual va a ser el size maximo del paquete a enviar


void inicializar_cliente(char*puerto, char*ip);
void envia_orden(char*msj);
void cerrar_cliente();
#endif
