
#ifndef HAMBURGESA_H
#define HAMBURGESA_H

//Prioridad de las hamburgesas
#define ALTA  "ALTA"
#define MEDIA "MEDIA"
#define BAJA  "BAJA"

//Rapidez de las hamburgesas
#define RAPIDO  5      //5 segundos
#define REGULAR 150    //2 minutos y 1/2
#define LENTO   300    //5 minutos

//Definición de mensajes para ejecución
#define COCINAR "COCINAR"

void cocinar_hamburgesa_alta();//cocina solo 1 hamburgesa rapido

void cocinar_hamburgesa_media();//cocina solo 1 hamburgesa regular

void cocinar_hamburgesa_baja();//cocina solo 1 hamburgesa lento

#endif
